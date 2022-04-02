import java.awt.Font;
import java.awt.event.ActionEvent;

import javax.swing.*;

import chess.Board;
import chess.Rules;
import control.GameController;
import view.GameView;

public class ChessGame {
    private Board board;
    private GameController controller;
    private GameView view;
    static Integer i=0;
    public static void main(String[] args) throws InterruptedException {
        ChessGame game = new ChessGame();
        game.init();
        game.run();
    }

    public void init() {
        controller = new GameController();
        board = controller.playChess();

        view = new GameView(controller);
        view.init(board);
        JFrame f=new JFrame("模式选择");
        f.setLayout(null);
        f.setVisible(true);
        f.setLocation(700, 500);//初始位置
        f.setResizable(false);
        f.setSize(300,300);
        f.setLocationRelativeTo(null);
        f.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        f.setAlwaysOnTop(true);
        JLabel l=new JLabel("HHU揭棋游戏");
        l.setLayout(null);
        l.setBounds(90,0,150,100);
        l.setFont(new Font("BOLD", 1, 20));
        f.add(l);
        JButton but1=new JButton("本地对战");
        JButton but2=new JButton("人机对战");
        but1.addActionListener((ActionEvent arg0)->{
        	i=1;
        	f.dispose();
        });
        but2.addActionListener((ActionEvent arg0)->{
        	i=2;
        	f.dispose();
        });
        but1.setBounds(100, 100, 90, 30);
        but2.setBounds(100, 160, 90, 30);
        f.add(but1);
        f.add(but2);
    }

    public void run() throws InterruptedException {
        while (controller.hasWin(board) == 'x') {
            view.showPlayer('r');
            /* User in. */
            while (board.player == 'r')
                Thread.sleep(50);
            
            if (controller.hasWin(board) != 'x')
                view.showWinner('r');
            view.showPlayer('b');
            /*player2*/
            if(i==1) {
            while (board.player == 'b')
                Thread.sleep(50);
            if (controller.hasWin(board) != 'x')
                view.showWinner('b');
            }
            /* AI in. */
            else if(i==2) {
        	while (board.player == 'r')
                Thread.sleep(50);
            
            if (controller.hasWin(board) != 'x')
                view.showWinner('r');
            view.showPlayer('b');
            int kkphbh=1;
            while(kkphbh==1) {
            	int[] bp=new int[] {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,30};
            	int bprn;
            	String bpname=new String();
            	double bpa = Math.random() * 16;
            	bpa = Math.ceil(bpa);
            	bprn = new Double(bpa).intValue()%16;
            	while(view.board.pieces[bp[bprn]].state!=true) {
            		bpa = Math.random() * 16;
            		bpa = Math.ceil(bpa);
            		bprn = new Double(bpa).intValue()%16;
            	}
            	System.out.println(bp[bprn]);
            	if(view.board.pieces[bp[bprn]].flag)bpname=view.board.pieces[bp[bprn]].second;
            	else bpname=view.board.pieces[bp[bprn]].first;
            	for(int[] kkk:Rules.getNextMove(bpname,view.board.pieces[bp[bprn]].position, view.board)) {
            		kkphbh=0;
            		if(view.board.cells[kkk[0]][kkk[1]]!=-1) {
            			view.pane.remove(view.lblPiece[view.board.cells[kkk[0]][kkk[1]]]);
            		}
            		if(!view.board.pieces[bp[bprn]].flag) {
            			view.lblPiece[view.board.pieces[bp[bprn]].key].setIcon(new ImageIcon("res/img/" + view.board.pieces[bp[bprn]].second.substring(0, 2) + ".png"));
            		}
            		view.controller.moveChess(view.board.pieces[bp[bprn]].key, kkk, view.board);
            		view.movePieceFromModel(view.board.pieces[bp[bprn]].key, kkk);
            		
            		break;
            	}
            }
            }
        }
        view.showWinner('b');
        ChessGame game = new ChessGame();
        game.init();
        game.run();
        
    }
}