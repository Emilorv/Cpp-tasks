#include "imgui-SFML.h"
#include "imgui.h"

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>

#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

#include <glm/glm.hpp>

#include <btBulletDynamicsCommon.h>

#include <chrono>

#include <iostream>

extern "C" {
// Implementation is in glut_shapes.c
void glutSolidCube(GLdouble size);
}

class Ground {
  btStaticPlaneShape shape;
  btDefaultMotionState motion_state;

public:
  btRigidBody body;

  Ground() : shape(btVector3(0.0, 1.0, 0.0), 0.0), body(0.0, &motion_state, &shape) {
    body.setRollingFriction(0.1);
    body.setRestitution(0.8);
  }

  void draw() {
    auto position = body.getCenterOfMassPosition();

    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(0.0, 1.0, 0.0);
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(position.x() - 5.0, position.y(), position.z() + 5.0);
    glVertex3f(position.x() - 5.0, position.y(), position.z() - 5.0);
    glVertex3f(position.x() + 5.0, position.y(), position.z() + 5.0);
    glVertex3f(position.x() + 5.0, position.y(), position.z() - 5.0);
    glEnd();
  }
};

class Sphere {
  btSphereShape shape;
  btDefaultMotionState motion_state;

public:
  btRigidBody body;

  Sphere() : shape(btScalar(0.1)), body(1.0, &motion_state, &shape) {
    auto mass = 1.0 / body.getInvMass();

    btVector3 inertia;
    shape.calculateLocalInertia(mass, inertia);

    body.setMassProps(mass, inertia);
    body.setRollingFriction(0.2);
    body.setRestitution(0.8);
  }

  void draw() {
    glPushMatrix();
    auto position = body.getCenterOfMassPosition();
    glTranslatef(position.x(), position.y(), position.z());
    glColor3f(0.0, 0.0, 1.0);
    auto quadric = gluNewQuadric();
    gluSphere(quadric, shape.getRadius(), 32, 32);
    gluDeleteQuadric(quadric);
    glPopMatrix();
  }
};

class Cube {
  btBoxShape shape;
  btDefaultMotionState motion_state;

public:
  btRigidBody body;

  Cube() : shape({0.1, 0.1, 0.1}), body(1.0, &motion_state, &shape) {
    auto mass = 1.0 / body.getInvMass();

    btVector3 inertia;
    shape.calculateLocalInertia(mass, inertia);

    body.setMassProps(mass, inertia);
    body.setFriction(0.5);
    body.setRollingFriction(0.1);
    body.setRestitution(0.2);
  }

  void draw() {
    glPushMatrix();
    auto position = body.getCenterOfMassPosition();
    glTranslatef(position.x(), position.y(), position.z());
    auto orientation = body.getOrientation();
    auto axis = orientation.getAxis().normalize();
    glRotatef(orientation.getAngle() * 180.0 / M_PI, axis.x(), axis.y(), axis.z());
    glColor3f(1.0, 0.0, 0.0);
    glutSolidCube(0.2);
    glPopMatrix();
  }
};

class World {
  btDefaultCollisionConfiguration collision_configuration;
  btCollisionDispatcher dispatcher;
  btDbvtBroadphase broadphase;
  btSequentialImpulseConstraintSolver solver;

public:
  btDiscreteDynamicsWorld dynamics;

  Ground ground;
  Sphere ground_sphere, falling_sphere;
  std::vector<Cube> cubes;
  const btVector3 initial_falling_sphere_position = btVector3(0.9, 3.0, 0.0);
  btVector3 falling_sphere_position = initial_falling_sphere_position;

  World() : dispatcher(&collision_configuration),
            dynamics(&dispatcher, &broadphase, &solver, &collision_configuration),
            cubes(6) {
    dynamics.setGravity(btVector3(0, -10.0, 0));

    worldInit(falling_sphere_position);
  }

  void worldInit(btVector3 initial_falling_sphere_position) {

    // Add objects to the physics engine
    dynamics.addRigidBody(&ground.body);
    dynamics.addRigidBody(&ground_sphere.body);
    dynamics.addRigidBody(&falling_sphere.body);
    for (auto &cube : cubes)
      dynamics.addRigidBody(&cube.body);

    btTransform transform;

    // Position ground
    transform.setIdentity();
    transform.setOrigin(btVector3(0.0, 0.0, 0.0));
    ground.body.setCenterOfMassTransform(transform);
    // Position spheres
    transform.setOrigin(btVector3(1.0, 0.1, 0.0));
    ground_sphere.body.setCenterOfMassTransform(transform);

    transform.setOrigin(initial_falling_sphere_position);
    falling_sphere.body.setCenterOfMassTransform(transform);

    // Position cubes
    transform.setOrigin(btVector3(-1.0, 0.1, -0.2));
    cubes[0].body.setCenterOfMassTransform(transform);
    transform.setOrigin(btVector3(-1.0, 0.1, 0.0));
    cubes[1].body.setCenterOfMassTransform(transform);
    transform.setOrigin(btVector3(-1.0, 0.1, 0.2));
    cubes[2].body.setCenterOfMassTransform(transform);
    transform.setOrigin(btVector3(-1.0, 0.3, -0.1));
    cubes[3].body.setCenterOfMassTransform(transform);
    transform.setOrigin(btVector3(-1.0, 0.3, 0.1));
    cubes[4].body.setCenterOfMassTransform(transform);
    transform.setOrigin(btVector3(-1.0, 0.5, 0.0));
    cubes[5].body.setCenterOfMassTransform(transform);
  }

  void reset() {
    cubes.clear();
    cubes.resize(6);

    for (int i = dynamics.getNumCollisionObjects() - 1; i >= 0; i--) {
      btCollisionObject *obj = dynamics.getCollisionObjectArray()[i];
      dynamics.removeCollisionObject(obj);
      delete obj;
    }
    ground = Ground();
    falling_sphere = Sphere();
    ground_sphere = Sphere();

    std::cout << dynamics.getNumCollisionObjects() << std::endl;
    worldInit(initial_falling_sphere_position);
  }

  void draw() {
    ground.draw();
    ground_sphere.draw();
    falling_sphere.draw();
    for (auto &cube : cubes)
      cube.draw();
  }
};

class Application {
  sf::ContextSettings context_settings;
  sf::RenderWindow window;

  World world;

public:
  Application() : context_settings(24),
                  window(sf::VideoMode(800, 600), "SFML Example", sf::Style::Default, context_settings) {
    window.setFramerateLimit(144);
    window.setVerticalSyncEnabled(true);

    // Various settings
    glClearColor(0.5, 0.5, 0.5, 0.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat light_position[] = {-3.0, 4.0, 0.0, 1.0};
    GLfloat spot_direction[] = {1.0, -1.0, -0.5};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.0);
    glEnable(GL_COLOR_MATERIAL);

    // Setup projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    gluPerspective(45.0, 4.0 / 3.0, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);

    // ImGui settings
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    ImGui::SFML::Init(window);
  }

  void start() {
    glm::vec3 camera(0.0, 1.0, 6.0);

    sf::Clock delta_clock;

    auto last_time = std::chrono::system_clock::now();
    bool running = true;
    bool startTimer = false;
    int number = 0;
    while (running) {
      // Handle events
      sf::Event event;
      while (window.pollEvent(event)) {
        ImGui::SFML::ProcessEvent(event);
        if (event.type == sf::Event::KeyPressed) {
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
            running = false;
          }
        } else if (event.type == sf::Event::Closed) {
          window.close();
          running = false;
        }
      }
      float horizontal_position = world.falling_sphere_position.x();
      float vertical_position = world.falling_sphere_position.y();

      ImGui::SFML::Update(window, delta_clock.restart());

      ImGui::Begin("ImGui");
      if (ImGui::Button("Restart game")) {
        startTimer = false;
        world.reset();
        /* horizontal_position = world.initial_falling_sphere_position.x();
         vertical_position = world.initial_falling_sphere_position.y();
         world.initPositions(world.initial_falling_sphere_position);*/
      }
      if (ImGui::Button("Drop ball")) {
        last_time = std::chrono::system_clock::now();
        startTimer = true;
        // Implementation needed
      }
      if (ImGui::SliderFloat("Horizontal ball position", &horizontal_position, 0.0, 10.0)) {
        startTimer = false;
        btTransform transform;
        world.falling_sphere_position.setX(horizontal_position);
        transform.setOrigin(world.falling_sphere_position);
        world.falling_sphere.body.setCenterOfMassTransform(transform);
      }
      if (ImGui::VSliderFloat("Vertical ball position", {20, 100}, &vertical_position, 0.0, 10.0)) {
        startTimer = false;
        btTransform transform;
        world.falling_sphere_position.setY(vertical_position);
        transform.setOrigin(world.falling_sphere_position);
        world.falling_sphere.body.setCenterOfMassTransform(transform);
      }
      ImGui::End();

      // Draw
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glLoadIdentity();

      gluLookAt(camera.x, camera.y, camera.z, // Camera position in World Space
                camera.x, camera.y, 0.0,      // Camera looks towards this position
                0.0, 1.0, 0.0);               // Up
      if (startTimer) {
        auto time = std::chrono::system_clock::now();
        world.dynamics.stepSimulation(std::chrono::duration<float>(time - last_time).count());
        last_time = time;
        number++;
        // std::cout << "Check " << number << std::endl;
      }

      world.draw();

      window.pushGLStates();
      ImGui::SFML::Render(window);
      window.popGLStates();

      // Swap buffer (show result)
      window.display();
    }
    ImGui::SFML::Shutdown();
  }
};

int main() {
  Application application;
  application.start();
}
