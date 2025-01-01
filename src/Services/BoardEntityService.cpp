package com.algos.puzzle.services;

import org.springframework.beans.factory.annotation.Autowired;
// import org.springframework.scheduling.annotation.Async;
import org.springframework.stereotype.Service;

import com.algos.puzzle.models.SearchNode;
import com.algos.puzzle.repositories.BoardRepository;

@Service
public class BoardEntityService {
  @Autowired
  private BoardRepository boardRepository;
  // @Async
  public void insertBoard(SearchNode currentNode ){
    boardRepository.insertBoard(
      currentNode.id, 
      currentNode.previous_board_id, 
      currentNode.board.toSave()
      // currentNode.board.hashCode(), 
      // currentNode.manhattanPriority(), 
      // currentNode.board.empty_row, 
      // currentNode.board.empty_column
    );
  }
}
