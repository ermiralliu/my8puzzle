// namespace puzzle.Helpers;

// public class Manager {

// 	private Manager() {}

// 	public static PriorityQueue<SearchNode, int> resize(PriorityQueue<SearchNode, int> boards) {
// 		SearchNode[] arr = boards.UnorderedItems.ToArray();	//adding this thing in the constructor is helpful
		
// 		var new_queue = Stream.of(arr)
// 				.sorted(SearchNode::compare)
// 				.limit(arr.length / 2 + arr.length/8) // allocates more often, but worked
// 				.collect( Collectors.toCollection(()-> new PriorityQueue<>(SearchNode::compare)));

// 		return new_queue;
// 	}
	

// }
