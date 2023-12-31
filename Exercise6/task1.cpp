#include <functional>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class ChessBoard {
public:
  enum class Color { WHITE,
                     BLACK };
  class Piece {
  public:
    Piece(Color color) : color(color) {}
    virtual ~Piece() {}

    Color color;
    std::string color_string() const {
      if (color == Color::WHITE)
        return "white";
      else
        return "black";
    }

    /// Return color and type of the chess piece
    virtual std::string type() const = 0;

    /// Returns true if the given chess piece move is valid
    virtual bool valid_move(int from_x, int from_y, int to_x, int to_y) const = 0;

    virtual std::string to_string() const = 0;
  };

  class King : public Piece {
  public:
    King(const Color color) : Piece(color) {}
    std::string type() const override {
      return "King";
    };
    bool valid_move(int from_x, int from_y, int to_x, int to_y) const override {
      // Checks if to-values are out of border
      if ((to_x < 0 || to_x >= 8) || (to_y < 0 || to_y >= 8)) {
        return false;
      }
      // Checks if the moves are valid for king
      int move_x = abs(to_x - from_x);
      int move_y = abs(to_y - from_y);
      if (move_x == 1 || move_y == 1) {
        return true;
      }
      return false;
    }
    std::string to_string() const override {
      return " " + color_string() + " " + type() + " ";
    }
  };

  class Knight : public Piece {
  public:
    Knight(const Color color) : Piece(color) {}
    std::string type() const override {
      return "Knight";
    };
    bool valid_move(int from_x, int from_y, int to_x, int to_y) const override {
      // Checks if to-values are out of border
      if ((to_x < 0 || to_x > 8) || (to_y < 0 || to_y > 8)) {
        return false;
      }
      int move_x = abs(to_x - from_x);
      int move_y = abs(to_y - from_y);

      if ((move_y == 1 && move_x == 2) || (move_y == 2 && move_x == 1)) {
        return true;
      }
      return false;
    }
    std::string to_string() const override {
      return color_string() + " " + type();
    }
  };

  class ChessBoardPrint {
  private:
    ChessBoard *board;

  public:
    ChessBoardPrint(ChessBoard &_board) {
      board = &_board;

      board->on_piece_move = [](const Piece &piece, const string &from, const string &to) {
        cout << piece.type() << " is moving from " << from << " to " << to << endl;
      };

      board->on_remove_piece = [](const Piece &piece_to, const string &to) {
        cout << piece_to.type() << " is being removed from " << to << endl;
      };

      board->on_piece_move_invalid = [](const Piece &piece_from, const string &from, const string &to) {
        cout << "can not move " << piece_from.type() << " from " << from << " to " << to << endl;
      };

      board->on_piece_move_missing = [](const string &from) {
        cout << "no piece at " << from << endl;
      };

      board->on_lost_game = [this](Color color) {
        this->lost_game(color);
      };

      board->after_piece_move = [this]() {
        this->print();
      };
    }

    void lost_game(Color color) {
      string lostColor = "";
      string wonColor = "";
      if (color == ChessBoard::Color::WHITE) {
        lostColor = "White";
        wonColor = "Black";
      } else {
        lostColor = "Black";
        wonColor = "White";
      }
      cout << lostColor << " lost the game" << endl;
      cout << wonColor << " won the game" << endl;
    }

    void print() {
      // Printing top-row with numbers
      cout << endl;
      cout << "   |";
      for (int i = 0; i < (int)board->squares.size(); i++) {
        cout << setfill(' ') << setw(6) << i + 1 << setw(7) << "|";
      }
      // Printing the first border and first letter
      char letters[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
      cout << endl
           << "    " << setfill('-') << setw(13 * 8 + 2) << " " << endl;
      cout << " " << letters[0] << " ";

      // Iterates each row
      for (int i = 0; i < (int)board->squares.size(); i++) {
        cout << "|";

        // Iterates each square
        for (int k = 0; k < (int)board->squares.size(); k++) {
          auto &piece = board->squares[i][k];
          // If piece, print piece. Else space
          if (piece) {
            cout << piece->to_string() << "|";
          } else {
            cout << setfill(' ') << setw(13) << "|";
          }
        }
        cout << endl;
        // Prints bottom border of each row and the letter on the next row, except if its the last row.
        cout << "    " << setfill('-') << setw(13 * 8 + 2) << " " << endl;
        if (i + 2 <= 8) {
          cout << " " << letters[i + 1] << " ";
        }
      }
      cout << endl;
    };
  };

  ChessBoard() {
    // Initialize the squares stored in 8 columns and 8 rows:
    squares.resize(8);
    for (auto &square_column : squares)
      square_column.resize(8);
  }

  /// 8x8 squares occupied by 1 or 0 chess pieces
  vector<vector<unique_ptr<Piece>>> squares;

  function<void(const Piece &piece, const string &from, const string &to)> on_piece_move;
  function<void(const Piece &piece, const string &square)> on_remove_piece;
  function<void(Color color)> on_lost_game;
  function<void(const Piece &piece, const string &from, const string &to)> on_piece_move_invalid;
  function<void(const string &square)> on_piece_move_missing;
  function<void()> after_piece_move;

  /// Move a chess piece if it is a valid move.
  /// Does not test for check or checkmate.
  bool move_piece(const std::string &from, const std::string &to) {
    int from_x = from[0] - 'a';
    int from_y = stoi(string() + from[1]) - 1;
    int to_x = to[0] - 'a';
    int to_y = stoi(string() + to[1]) - 1;

    auto &piece_from = squares[from_x][from_y];
    if (piece_from) {
      if (piece_from->valid_move(from_x, from_y, to_x, to_y)) {
        if (on_piece_move) {
          on_piece_move(*piece_from, from, to);
        }
        auto &piece_to = squares[to_x][to_y];
        if (piece_to) {
          if (piece_from->color != piece_to->color) {
            if (on_remove_piece) {
              on_remove_piece(*piece_to, to);
            }
            if (auto king = dynamic_cast<King *>(piece_to.get()))
              if (on_lost_game) {
                on_lost_game(king->color);
              }
          } else {
            // piece in the from square has the same color as the piece in the to square
            if (on_piece_move_invalid) {
              on_piece_move_invalid(*piece_from, from, to);
            }
            return false;
          }
        }
        piece_to = std::move(piece_from);
        if (after_piece_move) {
          after_piece_move();
        }
        return true;
      } else {
        if (on_piece_move_invalid) {
          on_piece_move_invalid(*piece_from, from, to);
        }
        return false;
      }
    } else {
      if (on_piece_move_missing) {
        on_piece_move_missing(from);
      }
      return false;
    }
  }
};

int main() {
  ChessBoard board;
  ChessBoard::ChessBoardPrint print(board);

  board.squares[4][0] = make_unique<ChessBoard::King>(ChessBoard::Color::WHITE);
  board.squares[1][0] = make_unique<ChessBoard::Knight>(ChessBoard::Color::WHITE);
  board.squares[6][0] = make_unique<ChessBoard::Knight>(ChessBoard::Color::WHITE);

  board.squares[4][7] = make_unique<ChessBoard::King>(ChessBoard::Color::BLACK);
  board.squares[1][7] = make_unique<ChessBoard::Knight>(ChessBoard::Color::BLACK);
  board.squares[6][7] = make_unique<ChessBoard::Knight>(ChessBoard::Color::BLACK);

  cout << "Invalid moves:" << endl;
  board.move_piece("e3", "e2");
  board.move_piece("e1", "e3");
  board.move_piece("b1", "b2");
  cout << endl;

  cout << "A simulated game:" << endl;
  print.print();
  board.move_piece("e1", "e2");
  board.move_piece("g8", "h6");
  board.move_piece("b1", "c3");
  board.move_piece("h6", "g8");
  board.move_piece("c3", "d5");
  board.move_piece("g8", "h6");
  board.move_piece("d5", "f6");
  board.move_piece("h6", "g8");
  board.move_piece("f6", "e8");
}
