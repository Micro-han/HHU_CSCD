package view;

import chess.Board;
import chess.Piece;
import chess.Rules;
import control.GameController;

import javax.swing.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

public class GameView {
    private static final int VIEW_WIDTH = 700, VIEW_HEIGHT = 712;
    private static final int PIECE_WIDTH = 67, PIECE_HEIGHT = 67;
    private static final int SY_COE = 68, SX_COE = 68;
    private static final int SX_OFFSET = 50, SY_OFFSET = 15;
    private Map<String, JLabel> pieceObjects = new HashMap<String, JLabel>();
    public Board board;
    private int selectedPieceKey=-1;
    private JFrame frame;
    public JLayeredPane pane;
    public GameController controller;
    private JLabel lblPlayer;
    public JLabel []lblPiece=new JLabel[32];

    public GameView(GameController gameController) {
        this.controller = gameController;
    }

    public void init(Board board) {
        this.board = board;
        frame = new JFrame("Blind Chinese Chess @HHU");
        frame.setIconImage(new ImageIcon("res/img/icon.png").getImage());
        frame.setSize(VIEW_WIDTH, VIEW_HEIGHT + 40);
        frame.setLocationRelativeTo(null);
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        pane = new JLayeredPane();
        frame.add(pane);

        /* Initialize chess board and listeners on each slot.*/
        JLabel bgBoard = new JLabel(new ImageIcon("res/img/board.png"));
        bgBoard.setLocation(0, 0);
        bgBoard.setSize(VIEW_WIDTH, VIEW_HEIGHT);
        bgBoard.addMouseListener(new BoardClickListener());
        pane.add(bgBoard, 1);

        /* Initialize player image.*/
        lblPlayer = new JLabel(new ImageIcon("res/img/r.png"));
        lblPlayer.setLocation(10, 320);
        lblPlayer.setSize(PIECE_WIDTH, PIECE_HEIGHT);
        pane.add(lblPlayer, 0);
        Piece[]pieces=board.pieces;
        for(int i=0;i<32;i++) {
        	int key=pieces[i].key;
        	String first=pieces[i].first;
        	int[] pos = pieces[i].position;
            int[] sPos = modelToViewConverter(pos);
            if(first=="bb0"||first=="rb0") {
            	lblPiece[i] = new JLabel(new ImageIcon("res/img/" + first.substring(0, 2) + ".png"));
            	lblPiece[i].setLocation(sPos[0], sPos[1]);     
                lblPiece[i].setSize(PIECE_WIDTH, PIECE_HEIGHT);
                lblPiece[i].addMouseListener(new PieceOnClickListener(key));
                pane.add(lblPiece[i], 0);
                //board.pieces[i].in=i;
            }
            else {
            	lblPiece[i] = new JLabel(new ImageIcon("res/img/bk.png"));
            	lblPiece[i].setLocation(sPos[0], sPos[1]);     
                lblPiece[i].setSize(PIECE_WIDTH, PIECE_HEIGHT);
                lblPiece[i].addMouseListener(new PieceOnClickListener(key));
                pane.add(lblPiece[i], 0);
                //board.pieces[i].in=i;
            }
        }
        /* Initialize chess pieces and listeners on each piece.*/
        /*Map<String, Piece> pieces = board.pieces;
        int i=0;
        for (Map.Entry<String, Piece> stringPieceEntry : pieces.entrySet()) {
            String key = stringPieceEntry.getKey();
            String first=stringPieceEntry.getValue().first;
            String second=stringPieceEntry.getValue().second;
            int[] pos = stringPieceEntry.getValue().position;
            int[] sPos = modelToViewConverter(pos);
            System.out.print(key+" "+first+" "+second+" ");
            System.out.println(board.pieces.get(key).second);
            if(first=="bb0"||first=="rb0") {
            	lblPiece[i] = new JLabel(new ImageIcon("res/img/" + first.substring(0, 2) + ".png"));
            	lblPiece[i].setLocation(sPos[0], sPos[1]);     
                lblPiece[i].setSize(PIECE_WIDTH, PIECE_HEIGHT);
                lblPiece[i].addMouseListener(new PieceOnClickListener(key));
                pieceObjects.put(stringPieceEntry.getKey(), lblPiece[i]);
                pane.add(lblPiece[i], 0);
                board.pieces.get(key).in=i;
                i++;
            }
            else {
            	lblPiece[i] = new JLabel(new ImageIcon("res/img/bk.png"));
            	lblPiece[i].setLocation(sPos[0], sPos[1]);     
                lblPiece[i].setSize(PIECE_WIDTH, PIECE_HEIGHT);
                lblPiece[i].addMouseListener(new PieceOnClickListener(key));
                pieceObjects.put(stringPieceEntry.getKey(), lblPiece[i]);
                pane.add(lblPiece[i], 0);
                board.pieces.get(key).in=i;
                i++;
            }
        }*/
        frame.setVisible(true);
    }


    public void movePieceFromModel(int pieceKey, int[] to) {
        //@SuppressWarnings("unlikely-arg-type")
		//JLabel pieceObject = pieceObjects.get(pieceKey+"");
        int[] sPos = modelToViewConverter(to);
        //pieceObject.setLocation(sPos[0], sPos[1]);
        lblPiece[pieceKey].setLocation(sPos[0], sPos[1]);
        /* Clear 'from' and 'to' info on the board */
        selectedPieceKey = -1;
    }

    public void movePieceFromAI(String pieceKey, int[] to) {
        int inNewPos = board.getPiece(to);
        if (inNewPos != -1) {
            pane.remove(pieceObjects.get(inNewPos));
            pieceObjects.remove(inNewPos);
        }

        JLabel pieceObject = pieceObjects.get(pieceKey);
        int[] sPos = modelToViewConverter(to);
        pieceObject.setLocation(sPos[0], sPos[1]);

        /* Clear 'from' and 'to' info on the board */
        selectedPieceKey = -1;
    }

    private int[] modelToViewConverter(int pos[]) {
        int sx = pos[1] * SX_COE + SX_OFFSET, sy = pos[0] * SY_COE + SY_OFFSET;
        return new int[]{sx, sy};
    }

    private int[] viewToModelConverter(int sPos[]) {
        /* To make things right, I have to put an 'additional sy offset'. God knows why. */
        int ADDITIONAL_SY_OFFSET = 25;
        int y = (sPos[0] - SX_OFFSET) / SX_COE, x = (sPos[1] - SY_OFFSET - ADDITIONAL_SY_OFFSET) / SY_COE;
        return new int[]{x, y};
    }

    public void showPlayer(char player) {
        lblPlayer.setIcon(new ImageIcon("res/img/" + player + ".png"));
        frame.setVisible(true);
    }

    public void showWinner(char player) {
        JOptionPane.showMessageDialog(null, (player == 'r') ? "Red player has won!" : "Black player has won!", "Intelligent Chinese Chess", JOptionPane.INFORMATION_MESSAGE);
//        System.exit(0);
    }

    class PieceOnClickListener extends MouseAdapter {
        private int key;
        private String name;
        PieceOnClickListener(int key) {
            this.key = key;
            
        }

        @Override
        public void mousePressed(MouseEvent e) {
        	System.out.println(key);
            if (selectedPieceKey != -1 && board.pieces[key].first.charAt(0) != board.player) {
            	boolean flag=board.pieces[selectedPieceKey].flag;
            	if(board.pieces[selectedPieceKey].flag) {
	            	this.name=board.pieces[selectedPieceKey].second;
	            }
	            else {
	            	this.name=board.pieces[selectedPieceKey].first;
	            	//board.pieces.get(selectedPieceKey).flag=true;
	            }
            	int[] pos = board.pieces[key].position;
                int[] selectedPiecePos = board.pieces[selectedPieceKey].position;                      
            	int in=board.pieces[selectedPieceKey].key;
            	String second=board.pieces[selectedPieceKey].second;
                /* If an enemy piece already has been selected.*/
                for (int[] each : Rules.getNextMove(name, selectedPiecePos, board)) {
                    if (Arrays.equals(each, pos)) {
                        // Kill self and move that piece.
                    	
                        //pane.remove(pieceObjects.get(key));
                    	pane.remove(lblPiece[key]);
                        pieceObjects.remove(key);
                        controller.moveChess(selectedPieceKey, pos, board);
                        movePieceFromModel(selectedPieceKey, pos);
                        if(!flag) {  
                        	lblPiece[in].setIcon(new ImageIcon("res/img/" + second.substring(0, 2) + ".png"));
                        }
                        selectedPieceKey=-1;
                        break;
                    }
                }
            } else if (board.pieces[key].first.charAt(0) == board.player) {
                /* Select the piece.*/
                selectedPieceKey = key;
            }
        }
    }

    class BoardClickListener extends MouseAdapter {
    	private String name;
        @Override
        public void mousePressed(MouseEvent e) {
            if (selectedPieceKey != -1) {
            	System.out.println(selectedPieceKey);
            	boolean flag=board.pieces[selectedPieceKey].flag;
            	if(board.pieces[selectedPieceKey].flag) {
                	this.name=board.pieces[selectedPieceKey].second;
                }
                else {
                	this.name=board.pieces[selectedPieceKey].first;
                	//board.pieces.get(selectedPieceKey).flag=true;
                }
                int[] sPos = new int[]{e.getXOnScreen() - frame.getX(), e.getYOnScreen() - frame.getY()};
                int[] pos = viewToModelConverter(sPos);
                int[] selectedPiecePos = board.pieces[selectedPieceKey].position;
            	int in=board.pieces[selectedPieceKey].key;
            	String second=board.pieces[selectedPieceKey].second;
                for (int[] each : Rules.getNextMove(name, selectedPiecePos, board)) {
                    if (Arrays.equals(each, pos)) {
                        controller.moveChess(selectedPieceKey, pos, board);
                        movePieceFromModel(selectedPieceKey, pos);
                        if(!flag) {
                        	//board.pieces.get(selectedPieceKey).flag=true;
                        	lblPiece[in].setIcon(new ImageIcon("res/img/" + second.substring(0, 2) + ".png"));
                        }
                        selectedPieceKey=-1;
                        break;
                    }
                }
            }
        }
    }

}
