/*----------------------------------------------------------
 *				HTBLA-Leonding / Klasse: 2AHIF
 * ---------------------------------------------------------
 * Exercise Number: 07
 * Title:			chess.cpp
 * Author:			David Ignjatovic
 * Due Date:		November 10, 2018
 * ----------------------------------------------------------
 * Description:
 * Implementation of basic chess functions.
 * ----------------------------------------------------------
 */
 #ifndef __CHESS_CPP
 #define __CHESS_CPP
 #include "math.h"
 #include "chess.h"


 bool is_square_ok (File file, Rank rank)
 {
  return (file <= 'h' && file >= 'a' && rank >= 1 && rank <= 8 );
 }
 bool is_move_from_base_line (enum PieceColor color, Rank rank)
 {
   if (color == Black) {
     return (rank < 8);
   }
   if (color == White) {
     return (rank > 1);
   }

   return false;
 }
 bool is_piece (struct ChessPiece pc, enum PieceColor color, enum PieceType type)
 {
   return (pc.color == color && pc.type == type);
 }
 void init_chess_board (ChessBoard chess_board)
 {
   for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      chess_board[x][y].is_occupied = false;
    }
   }
 }
 struct ChessSquare * get_square (ChessBoard chess_board, File file, Rank rank)
 {
   if (is_square_ok(file, rank)) {
     return &chess_board[rank- 1][file-'a'];
   }
   return 0;
 }
 bool is_square_occupied (ChessBoard chess_board, File file, Rank rank)
 {
  return (chess_board[file - 1][rank - 1].is_occupied);
 }
 bool add_piece (ChessBoard chess_board, File file, Rank rank, struct ChessPiece piece)
  {
    if (chess_board[rank- 1][file-'a'].is_occupied == false && is_square_ok(file, rank) == true) {
      chess_board[rank- 1][file-'a'].is_occupied = true;
      chess_board[rank- 1][file-'a'].piece = piece;
      return true;
    }
    return false;
  }
 struct ChessPiece get_piece (ChessBoard chess_board, File file, Rank rank)
 {
   return chess_board[rank- 1][file-'a'].piece;
 }
 void setup_chess_board (ChessBoard chess_board)
 {
   init_chess_board(chess_board);
  for (char x = 'a'; x <= 'h'; x++)
  {
    add_piece(chess_board, x, 2, {White, Pawn});
    add_piece(chess_board, x, 7, {Black, Pawn});
  }
 }
 bool remove_piece (ChessBoard chess_board, File file, Rank rank)
 {
   if (is_square_occupied(chess_board,file,rank) == true) {
     chess_board[rank- 1][file-'a'] = {0};
     return true;
   }
   return false;
 }
 bool squares_share_file (File s1_f, Rank s1_r, File s2_f, Rank s2_r)
 {
   return (s1_f == s2_f);
 }
 bool squares_share_rank (File s1_f, Rank s1_r, File s2_f, Rank s2_r)
 {
   return (s1_r == s2_r);
 }
 bool squares_share_diagonal (File s1_f, Rank s1_r, File s2_f, Rank s2_r)
 {
   return true; //couldn't understand it
 }
 bool squares_share_knights_move (File s1_f, Rank s1_r, File s2_f, Rank s2_r)
 {
   if (is_square_ok(s1_f,s1_r) == true && is_square_ok(s2_f,s2_r) == true) {
     return squares_share_diagonal(s1_f, s1_r, s2_f, s2_r);
   }
   return false;
 }
 bool squares_share_pawns_move (enum PieceColor color, enum MoveType move, File s1_f, Rank s1_r, File s2_f, Rank s2_r)
 {
   if (s1_r+1 == s2_r && (s1_f-1 == s2_f || s1_f+1 == s2_f)) {
     move = CaptureMove;
   }else{move = NormalMove;}
   return (move == CaptureMove);
 }
 bool squares_share_queens_move (File s1_f, Rank s1_r, File s2_f, Rank s2_r)
 {
   if (is_square_ok(s1_f,s1_r) == true && is_square_ok(s2_f,s2_r) == true)
   {
       return (squares_share_diagonal(s1_f, s1_r, s2_f, s2_r) == true || s1_f == s2_f || s1_r == s2_r );
   }
   return false;
 }
 bool squares_share_kings_move (File s1_f, Rank s1_r, File s2_f, Rank s2_r)
 {
   if (is_square_ok(s1_f,s1_r) == true && is_square_ok(s2_f,s2_r) == true) {
      if (s1_r == s2_r-1 || s2_r == s1_r-1 || s2_r == s1_r) {
        return true;
   }
  }
  return false;
 }
#endif
