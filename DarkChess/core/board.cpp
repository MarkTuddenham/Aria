#include <map>
#include <vector>
#include <algorithm>
#include <memory>

#include "DarkChess/core/board.hpp"
#include "DarkChess/core/piece.hpp"
#include "DarkChess/core/utils.hpp"
#include "DarkChess/core/log.hpp"

namespace DarkChess
{

ChessBoard::ChessBoard() : ChessBoard(false) {}

ChessBoard::ChessBoard(bool t_debug) : debug(t_debug)
{

    auto make_piece = [&](ChessPiece cp, int i) {
        std::shared_ptr<ChessPiece> cp_ptr = std::make_shared<ChessPiece>(cp);
        m_board.insert({i, cp_ptr});
        m_moves.insert({cp_ptr, std::make_shared<MoveList>(MoveList())});
    };

    // White pawns (1,0) -> (1,7)
    for (int i = 8; i < 16; ++i)
        make_piece(ChessPiece(WHITE, PAWN), i);

    // Black pawns (6,0) -> (6,7)
    for (int i = 48; i < 56; ++i)
        make_piece(ChessPiece(BLACK, PAWN), i);

    // Knights
    make_piece(ChessPiece(WHITE, KNIGHT), 1);
    make_piece(ChessPiece(WHITE, KNIGHT), 6);
    make_piece(ChessPiece(BLACK, KNIGHT), 57);
    make_piece(ChessPiece(BLACK, KNIGHT), 62);

    // Bishops
    make_piece(ChessPiece(WHITE, BISHOP), 2);
    make_piece(ChessPiece(WHITE, BISHOP), 5);
    make_piece(ChessPiece(BLACK, BISHOP), 58);
    make_piece(ChessPiece(BLACK, BISHOP), 61);

    // Rooks
    make_piece(ChessPiece(WHITE, ROOK), 0);
    make_piece(ChessPiece(WHITE, ROOK), 7);
    make_piece(ChessPiece(BLACK, ROOK), 56);
    make_piece(ChessPiece(BLACK, ROOK), 63);

    // Queens
    make_piece(ChessPiece(WHITE, QUEEN), 3);
    make_piece(ChessPiece(BLACK, QUEEN), 59);

    // Kings
    make_piece(ChessPiece(WHITE, KING), 4);
    make_piece(ChessPiece(BLACK, KING), 60);

    generate_moves();
}

int ChessBoard::get_num_moves() const
{
    return numMoves;
}

PieceColour ChessBoard::get_turn() const
{
    return m_turn;
}

const std::string ChessBoard::get_turn_name() const
{
    return piece_colour_string.at(m_turn);
}

const std::unique_ptr<BoardMap> ChessBoard::get_pieces() const
{
    return std::make_unique<BoardMap>(m_board);
}

const std::shared_ptr<ChessPiece> ChessBoard::get_piece(int t_ind) const
{
    if (m_board.find(t_ind) == m_board.end())
        return nullptr;
    else
        return m_board.at(t_ind);
}

const std::shared_ptr<ChessPiece> ChessBoard::get_piece(Position t_pos) const
{
    return get_piece(get_index_from_pos(t_pos));
}

void ChessBoard::swap_turn()
{
    m_turn = PieceColour((m_turn + 1) % 2);
    DC_CORE_TRACE("{}'s turn.", get_turn_name());
}

void ChessBoard::move(int t_from_ind, int t_to_ind)
{
    // If in debug mode then can move any piece anywhere.

    // TODO? raise errors instead of return if can't move

    const std::shared_ptr<ChessPiece> p = get_piece(t_from_ind);

    // check if there is a piece to move
    if (!p)
    {
        DC_CORE_WARN("Invalid move! No Piece.");
        return;
    }

    // check piece is of the correct colour
    // If we're debugging then allow out of turn moves
    if (!debug && p->get_colour() != m_turn)
    {
        DC_CORE_WARN("Invalid move! Not your turn.");
        return;
    }

    //TODO check legal move
    // if (!debug && !get_legal_moves(from).contains(to))
    // {
    //     std::cerr << "Invalid move! Not a legal move." << std::endl;
    //     return;
    // }

    // Add piece in its new place
    m_board[t_to_ind] = m_board[t_from_ind];

    // remove piece from old position
    m_board.erase(t_from_ind);

    // Swap turns
    swap_turn();
    numMoves++;

    DC_CORE_INFO("Move: {} from {} to {}",
                 p->get_name(),
                 std::to_string(get_pos_from_index(t_to_ind)),
                 std::to_string(get_pos_from_index(t_from_ind)));

    // Regenerate possible moves
    generate_moves();
}

void ChessBoard::move(Position t_from_pos, Position t_to_pos)
{
    move(get_index_from_pos(t_from_pos), get_index_from_pos(t_to_pos));
}

void ChessBoard::generate_moves()
{
    for (auto ind_piece_pair : m_board)
        generate_piece_moves(ind_piece_pair.first);
}

void ChessBoard::generate_piece_moves(const std::shared_ptr<ChessPiece> t_cp)
{
    int ind = -1;

    // for (auto itr = m_board.begin(); itr != m_board.end(); itr++)
    for (auto ind_piece_pair : m_board)
    {
        if (t_cp == ind_piece_pair.second)
        {
            ind = ind_piece_pair.first;
            break;
        }
    }
    return generate_piece_moves(ind);
}

void ChessBoard::generate_piece_moves(int t_ind)
{

    // get current piece from board
    const std::shared_ptr<ChessPiece> cp = get_piece(t_ind);

    if (!cp)
    {
        DC_CORE_ERROR("Unknown Piece!");
        return;
    }

    const std::shared_ptr<MoveList> piece_moves = get_moves(cp);
    piece_moves->clear();

    const Position current_pos = get_pos_from_index(t_ind);

    auto add_moves_from_relative = [&](std::vector<Position> relative_moves) {
        for (Position rel_move_pos : relative_moves)
        {
            const Position abs_move_pos = current_pos + rel_move_pos;

            if (out_of_bounds(abs_move_pos))
                continue;

            const std::shared_ptr<ChessPiece> possible_capture = get_piece(abs_move_pos);

            // If there is not a piece, or the piece is capturable
            if (!possible_capture || (possible_capture && possible_capture->get_colour() != cp->get_colour()))
            {
                piece_moves->push_back(get_index_from_pos(abs_move_pos));
            }
        }
    };

    switch (cp->get_type())
    {
    case PAWN:
    {
        //rotation based on colour -> only applies to pawns.
        int rotation = (cp->get_colour() == WHITE) ? 1 : -1;

        // Check forward move
        {
            const Position rel_move_pos = {0, 1};
            const Position abs_move_pos = current_pos + rel_move_pos * rotation;

            const std::shared_ptr<ChessPiece> in_front_piece = get_piece(abs_move_pos);

            if (!in_front_piece && !out_of_bounds(abs_move_pos))
                piece_moves->push_back(get_index_from_pos(abs_move_pos));
        }

        // Check capturing moves
        for (Position rel_move_pos : std::vector<Position>{{-1, 1}, {1, 1}})
        {
            const Position abs_move_pos = current_pos + rel_move_pos * rotation;

            if (out_of_bounds(abs_move_pos))
                continue;

            const std::shared_ptr<ChessPiece> possible_capture = get_piece(abs_move_pos);

            if (possible_capture && possible_capture->get_colour() != cp->get_colour())
                piece_moves->push_back(get_index_from_pos(abs_move_pos));
        }

        break;
    }

    case KNIGHT:
    {
        add_moves_from_relative({{1, 2},
                                 {2, 1},
                                 {-1, 2},
                                 {-2, 1},
                                 {1, -2},
                                 {2, -1},
                                 {-1, -2},
                                 {-2, -1}});
        break;
    }

    case BISHOP:
    {
        ad_infinitum(t_ind,
                     {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}},
                     piece_moves);
        break;
    }

    case ROOK:
    {
        ad_infinitum(t_ind,
                     {{0, 1}, {1, 0}, {0, -1}, {-1, 0}},
                     piece_moves);
        break;
    }

    case QUEEN:
    {
        ad_infinitum(t_ind,
                     {{1, 1},
                      {1, -1},
                      {-1, 1},
                      {-1, -1},
                      {0, 1},
                      {1, 0},
                      {0, -1},
                      {-1, 0}},
                     piece_moves);
        break;
    }

    case KING:
    {
        add_moves_from_relative({{1, 1},
                                 {1, -1},
                                 {-1, 1},
                                 {-1, -1},
                                 {0, 1},
                                 {1, 0},
                                 {0, -1},
                                 {-1, 0}});

        break;
    }

    default:
        // TODO raise error
        DC_CORE_ERROR("Unknown Piece.");
        break;
    }
} // namespace DarkChess

void ChessBoard::ad_infinitum(int t_ind, std::vector<Position> t_directions, std::shared_ptr<MoveList> t_movelist)
{
    const Position pos = get_pos_from_index(t_ind);
    const std::shared_ptr<ChessPiece> cp = get_piece(t_ind);

    for (Position dir : t_directions)
    {
        // There can only be a max of 7 iterations before going out of bounds
        // start at 1 since 0 will be the current position.
        for (int i = 1; i < 8; ++i)
        {
            const Position to_pos = pos + dir * i;

            if (out_of_bounds(to_pos))
                break;

            const std::shared_ptr<ChessPiece> to_piece = get_piece(to_pos);

            if (!to_piece)
            {
                // Found no piece: Keep looking in this direction.
                t_movelist->push_back(get_index_from_pos(to_pos));
                continue;
            }
            else if (to_piece->get_colour() != cp->get_colour())
            {
                // Found enemy piece: Stop looking in this direction.
                t_movelist->push_back(get_index_from_pos(to_pos));
                break;
            }
            else
            {
                break;
            }
        }
    }
}

const std::shared_ptr<MoveList> ChessBoard::get_moves(std::shared_ptr<ChessPiece> t_cp) const
{
    if (!t_cp || m_moves.find(t_cp) == m_moves.end())
        return nullptr;
    else
        return m_moves.at(t_cp);
}

const std::shared_ptr<MoveList> ChessBoard::get_moves(int t_ind) const
{
    return get_moves(get_piece(t_ind));
}

const std::shared_ptr<MoveList> ChessBoard::get_moves(Position t_pos) const
{
    return get_moves(get_index_from_pos(t_pos));
}

const std::shared_ptr<MoveList> ChessBoard::get_legal_moves(std::shared_ptr<ChessPiece> t_cp) const
{
    // TODO detect if places in check
    const std::shared_ptr<MoveList> all_moves = get_moves(t_cp);

    return all_moves;
}

const std::shared_ptr<MoveList> ChessBoard::get_legal_moves(int t_ind) const
{
    return get_legal_moves(get_piece(t_ind));
}

const std::shared_ptr<MoveList> ChessBoard::get_legal_moves(Position t_pos) const
{
    return get_legal_moves(get_index_from_pos(t_pos));
}

std::string ChessBoard::to_string() const
{

    std::string str;

    str += "\n  ---------------------------------\n";

    for (int y = 7; y >= 0; y--)
    {
        str += std::to_string(y) + " ";
        for (int x = 0; x < 8; x++)
        {
            char sym;
            std::shared_ptr<ChessPiece> cp = get_piece({x, y});

            if (cp)
                sym = cp->get_symbol();
            else
                sym = ' ';

            str += "| ";
            str.push_back(sym);
            str += " ";
        }
        str += "|\n  ---------------------------------\n";
    }

    str += "    0   1   2   3   4   5   6   7  \n";

    return str;
}

} // namespace DarkChess