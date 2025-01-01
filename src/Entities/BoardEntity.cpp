
public class BoardEntity { // this is like board and searchnode together

  public int id;

  public int parent_id;

  public byte[] board_arr;
  
 public BoardEntity(int id, int parent_id, byte[] board_arr){
    this.id = id;
    this.parent_id = parent_id;
    this.board_arr = board_arr;
  }

  // public Integer hash;

  // public Integer manhattanPriority;

  // public Integer emptyRow;

  // public Integer emptyColumn;
 
}
