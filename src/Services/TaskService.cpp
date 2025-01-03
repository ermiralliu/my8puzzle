// package com.algos.puzzle.services;

// import java.util.concurrent.BlockingQueue;
// import java.util.concurrent.ExecutorService;
// import java.util.concurrent.Executors;
// import java.util.concurrent.LinkedBlockingQueue;

// public class TaskService {
//   private final ExecutorService executorService = Executors.newSingleThreadExecutor();
//   private final BlockingQueue<Runnable> taskQueue = new LinkedBlockingQueue<>();

//   public void startThread() {
//     executorService.submit(() -> {
//       try {
//         while (true) {
//           Runnable task = taskQueue.take();
//           task.run();
//         }
//       } catch (InterruptedException e) {
//         Thread.currentThread().interrupt();
//       }
//     });
//   }

//   public void addTask(Runnable r){
//     taskQueue.add(r);
//   }

//   public void clear(){
//     taskQueue.clear();
//   }

//   public void close(){
//     executorService.shutdown();
//   }
// }
