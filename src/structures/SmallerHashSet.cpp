// namespace puzzle.Structures;

// public struct SmallerHashSet<T>
// {
//   private CustomList<T>[] _buckets;
//   private readonly int Size => _buckets.Length;
//   private int _count = 0;
//   public readonly int Count => _count;
//   public void Clear()
//   {
//     _buckets = [];
//     _count = 0;
//   }

//   public SmallerHashSet(int size)
//   {
//     _buckets = new CustomList<T>[size];
//     for (int i = 0; i < size; i++)
//     {
//       _buckets[i] = [];
//     }
//   }

//   private void Resize()
//   {
//     var bigger = new SmallerHashSet<T>(Size * 2);
//     foreach (var list in _buckets)
//     {
//       foreach (var element in list)
//       {
//         bigger.Add(element);
//       }
//     }
//     _buckets = bigger._buckets;
//     // theint Size remains the same
//   }


//   public bool Add(T item)
//   {
//     int hash = Math.Abs(item!.GetHashCode()) % Size;
//     if (_buckets[hash].Contains(item))
//     {
//       return false; // Item already exists
//     }
//     if (_count == Size - 1)
//     {
//       Resize();
//     }
//     _buckets[hash].Add(item);
//     _count++;
//     return true;
//   }

//   public readonly bool Contains(T item)
//   {
//     int hash = Math.Abs(item!.GetHashCode()) % Size;
//     return _buckets[hash].Contains(item);
//   }

//   public bool Remove(T item)
//   {
//     int hash = Math.Abs(item!.GetHashCode()) % Size;
//     _count--;
//     return _buckets[hash].Remove(item);
//   }

//   public readonly int MaxCollisions(){
//     return _buckets.Max( element => element.Count );
//   }
// }
