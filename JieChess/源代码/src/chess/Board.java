package chess;

import java.util.Map;

public class Board{
    public final int BOARD_WIDTH = 9, BOARD_HEIGHT = 10;
    //public Map<String, Piece> pieces;
    public Piece[]pieces=new Piece[40];
    public char player = 'r';
    //private Piece[][] cells = new Piece[BOARD_HEIGHT][BOARD_WIDTH];
    public int[][]cells=new int[BOARD_HEIGHT][BOARD_WIDTH];
    {
    	for(int i=0;i<BOARD_HEIGHT;i++) {
    		for(int j=0;j<BOARD_WIDTH;j++) {
    			cells[i][j]=-1;
    		}
    	}
    }
    public boolean isInside(int[] position) {
        return isInside(position[0], position[1]);
    }

    public boolean isInside(int x, int y) {
        return !(x < 0 || x >= BOARD_HEIGHT
                || y < 0 || y >= BOARD_WIDTH);
    }

    public boolean isEmpty(int[] position) {
        return isEmpty(position[0], position[1]);
    }

    public boolean isEmpty(int x, int y) {
        return isInside(x, y) && cells[x][y] == -1;
    }


    public boolean update(Piece piece) {
        int[] pos = piece.position;
        cells[pos[0]][pos[1]] = piece.key;
        return true;
    }

    public void updatePiece(int key, int[] newPos) {
        Piece orig = pieces[key];
        //Piece inNewPos = getPiece(newPos);
        int inNewPos=cells[newPos[0]][newPos[1]];
        /* If the new slot has been taken by another piece, then it will be killed.*/
        if (inNewPos!=-1)
            pieces[inNewPos].state=false;
        /* Clear original slot and updatePiece new slot.*/
        int[] origPos = orig.position;
        cells[origPos[0]][origPos[1]] = -1;
        cells[newPos[0]][newPos[1]] = key;
        orig.position = newPos;
        player = (player == 'r') ? 'b' : 'r';
        //return inNewPos;
    }

    public boolean backPiece(int key) {
        int[] origPos = pieces[key].position;
        cells[origPos[0]][origPos[1]] = pieces[key].key;
        return true;
    }

    public int getPiece(int[] pos) {
        return getPiece(pos[0], pos[1]);
    }

    public int getPiece(int x, int y) {
        return cells[x][y];
    }
}