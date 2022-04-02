package control;

import alogrithm.AlphaBetaNode;
import alogrithm.SearchModel;
import chess.Board;
import chess.Piece;
import view.GameView;

import java.util.HashMap;
import java.util.Map;

public class GameController {

    private Piece[] initPieces() {
        Piece[] pieces=new Piece[40];
    	//Piece[] pieces = new HashMap<String, Piece>();
        int [][]pos= {{0, 0},{0, 1},{0, 2},{0, 3},{0, 5},{0, 6},{0, 7},{0, 8},{2, 1},{2, 7},{3, 0},
        		{3, 2},{3, 4},{3, 6},{3, 8},{9, 0},{9, 1},{9, 2},{9, 3},{9, 5},{9, 6},{9, 7},{9, 8},
        		{7, 1},{7, 7},{6, 0},{6, 2},{6, 4},{6, 6},{6, 8}};
        int []rand=new int[16];
        int []rand1=new int[16];
        boolean []book=new boolean [32];
        for(int i=0;i<30;i++) {
        	book[i] = false;
        }
        for (int j = 0; j < 15; ) {
	       	double a = Math.random() * 15;
	       	a = Math.ceil(a);
	       	int randomNum = new Double(a).intValue()%15;
	       	if(book[randomNum])continue;
        	book[randomNum]= true;
        	rand[j]=randomNum;
        	j++;
       	}
        for (int j = 0; j < 15; ) {
	       	double a = Math.random() * 15;
	       	a = Math.ceil(a);
	       	int randomNum = new Double(a).intValue()%15+15;
	       	if(book[randomNum])continue;
        	book[randomNum]= true;
        	rand1[j]=randomNum;
        	j++;
       	}
        String []str=new String[]{"bj0","bm0","bx0","bs0","bs1","bx1","bm1","bj1","bp0","bp1",
        		"bz0","bz1","bz2","bz3","bz4","rj0","rm0","rx0","rs0","rs1","rx1","rm1",
        		"rj1","rp0","rp1","rz0","rz1","rz2","rz3","rz4"};
        for(int i=0;i<15;i++) {
        	pieces[i]= new Piece(i,str[rand[i]],str[i],pos[rand[i]]);
        }
        for(int i=0;i<15;i++) {
        	pieces[i+15]= new Piece(i+15,str[rand1[i]],str[i+15],pos[rand1[i]]);
        }
        pieces[30]= new Piece(30,"bb0","bb0",new int[]{0, 4});
        pieces[31]= new Piece(31,"rb0","rb0",new int[]{9, 4});
        
        return pieces;
    }

    private Board initBoard() {
        Board board = new Board();
        board.pieces = initPieces();
        //for (Map.Entry<String, Piece> stringPieceEntry : initPieces().entrySet()) board.update(stringPieceEntry.getValue());
        for(int i=0;i<32;i++)board.update(board.pieces[i]);
        return board;
    }


    public Board playChess() {
        /**
         * Start game.
         * */
        initPieces();
        return initBoard();
    }


    public void moveChess(int key, int[] position, Board board) {
        /**
         * Implements user's action.
         * */
        board.updatePiece(key, position);
        board.pieces[key].flag=true;
    }


    public void responseMoveChess(Board board, GameView view) {
        /**
         * Implements artificial intelligence.
         * */
        SearchModel searchModel = new SearchModel();
        AlphaBetaNode result = searchModel.search(board);

        view.movePieceFromAI(result.piece, result.to);
        //board.updatePiece(result.piece.key, result.to);
    }


    public void printBoard(Board board) {
        /**
         * Piece position is stored internally as [row, col], but output standard requires [col,row].
         * Here comes the conversion.
         * eg. [0, 4] --> [E, 0]
         * */
        Piece[] pieces = board.pieces;
        /*for (Map.Entry<String, Piece> stringPieceEntry : pieces.entrySet()) {
            Piece piece = stringPieceEntry.getValue();
            System.out.println(stringPieceEntry.getKey() + ":" + (char) (piece.position[1] + 'A') + piece.position[0]);
        }*/
        for(int i=0;i<pieces.length;i++) {
        	Piece piece=pieces[i];
        	System.out.println(piece.key + ":" + (char) (piece.position[1] + 'A') + piece.position[0]);
        }

        System.out.println();
    }

    public char hasWin(Board board) {
        /**
         * Judge has the game ended.
         * @return 'r' for RED wins, 'b' for BLACK wins, 'x' for game continues.
         * */
        boolean isRedWin = board.pieces[30].state == false;
        boolean isBlackWin = board.pieces[31].state == false;
        if (isRedWin) return 'r';
        else if (isBlackWin) return 'b';
        else return 'x';
    }

}
