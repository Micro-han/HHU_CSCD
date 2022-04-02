package chess;

public class Piece implements Cloneable {
    public int key;
    public String first;
    public String second;
    public boolean flag;
    public char color;
    public char character;
    public char index;
    public int[] position = new int[2];
    public boolean state;
    //public int in;

    public Piece(int name,String first,String second, int[] position) {
        this.key = name;
        this.color = first.charAt(0);
        this.character = first.charAt(1);
        this.index = first.charAt(2);
        this.position = position;
        this.flag=false;
        this.first=first;
        this.second=second;
        this.state=true;
    }

}
