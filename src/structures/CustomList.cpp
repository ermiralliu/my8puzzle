// I might use this, but set in here, is also good

// namespace puzzle.Structures;

// using System.Collections;

// public class CustomList<T> : IEnumerable<T>
// {
//   private T[] _items = new T[1];
//   private int _count = 0;

//   public int Count => _count;

//   public void Add(T item)
//   {
//     if (_count == _items.Length)
//     {
//       Resize();
//     }
//     _items[_count++] = item;
//   }

//   private void Resize()
//   {
//     T[] newItems = new T[_items.Length + 2];
//     Array.Copy(_items, newItems, _items.Length);
//     _items = newItems;
//   }

//   public bool Remove(T item)
//   {
//     int index = Array.IndexOf(_items, item, 0, _count);
//     if (index < 0)
//     {
//       return false;
//     }

//     _count--;
//     Array.Copy(_items, index + 1, _items, index, _count - index);
// #pragma warning disable CS8601 // Possible null reference assignment.
//     _items[_count] = default;
// #pragma warning restore CS8601 // Possible null reference assignment.
//     return true;
//   }

//   public void Clear()
//   {
//     _items = new T[2];
//     _count = 0;
//   }

//   public T this[int index]
//   {
//     get
//     {
//       if (index < 0 || index >= _count)
//       {
//         throw new ArgumentOutOfRangeException(nameof(index));
//       }
//       return _items[index];
//     }
//     set
//     {
//       if (index < 0 || index >= _count)
//       {
//         throw new ArgumentOutOfRangeException(nameof(index));
//       }
//       _items[index] = value;
//     }
//   }

//   public IEnumerator<T> GetEnumerator()
//   {
//     for (int i = 0; i < _count; i++)
//     {
//       yield return _items[i];
//     }
//   }

//   IEnumerator IEnumerable.GetEnumerator()
//   {
//     return GetEnumerator();
//   }
// }
