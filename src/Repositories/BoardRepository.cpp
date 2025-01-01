package com.algos.puzzle.repositories;

import java.util.Optional;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Modifying;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;
import org.springframework.lang.NonNull;
import org.springframework.stereotype.Repository;

import com.algos.puzzle.entities.BoardEntity;

import jakarta.transaction.Transactional;

@Repository
public interface BoardRepository extends JpaRepository<BoardEntity,Long>{
  @NonNull 
  Optional<BoardEntity> findById(@NonNull Long id);

  @Modifying
  @Transactional
  @Query(value = """
    INSERT INTO board_entity (id, parent_id, board_string)
    VALUES (:id, :parentId, :boardString)
  """ , nativeQuery = true)
  public int insertBoard(
    @Param("id") long id,
    @Param("parentId") long parentId,
    @Param("boardString") String boardString
    // @Param("hash") int hash,
    // @Param("manhattanPriority") int manhattanPriority,
    // @Param("emptyRow") int emptyRow,
    // @Param("empty_column") int empty_column
  );
}
