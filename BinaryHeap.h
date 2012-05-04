//*******************************************************************************
//
// /Library/Collections/BinaryHeap.h
//
// Copyright 2011 COPYRIGHT_HOLDER
// 
// LICENCE
//
// Author: Adam J. Naylor
//
//*******************************************************************************

#ifndef __LIBRARY_COLLECTIONS_BINARYHEAP_H__
#define __LIBRARY_COLLECTIONS_BINARYHEAP_H__




namespace Rise
{

	///
	/// A BinaryHeap implementation.
	/// Based losely on readings from: http://www.policyalmanac.org/games/binaryHeaps.htm
	///
	template<class T, int SIZE>
	class BinaryHeap
	{
	public:
		//--------------------------------------------------------------------------------
		///
		/// Constructs an empty BinaryHeap.
		///
		//--------------------------------------------------------------------------------
				BinaryHeap() : _count(0) {};

		//--------------------------------------------------------------------------------
		///
		/// Adds an item to the heap, ensuring it is added to the correct place.
		///
		/// @param item
		///   The item to add. Duplicates are allowed.
		///
		//--------------------------------------------------------------------------------
		void	Add(T item);

		//--------------------------------------------------------------------------------
		///
		/// Pops the first item from the heap and resorts the remaining items.
		///
		//--------------------------------------------------------------------------------
		T		RemoveFirst();

		//--------------------------------------------------------------------------------
		///
		/// Gets the size of the heap.
		///
		//--------------------------------------------------------------------------------
		int		Get_Size() { return _count; }

	private:
		T		_data[SIZE];
		int		_count;
	};

	template<class T, int SIZE>
	void BinaryHeap<T, SIZE>::Add(T item)
	{
		if (_count >= SIZE) return;
		
		if (_count == 0)
		{
			_data[_count++] = item;
			return;
		}
		
		int parent;
		_data[_count] = item; //start at the end
		for (int i = _count; i > 0; i = parent) //opti check division?
		{
			parent = i/2;
			if (_data[i] >= _data[parent])
			{
				break; //we have found the right spot
			}
			else //swap them and continue up the chain
			{
				_data[i] = _data[parent];
				_data[parent] = item;
			}
		}
		++_count;

	}

	template<class T, int SIZE>
	T BinaryHeap<T, SIZE>::RemoveFirst()
	{
		if (_count == 0) return 0;

		T result = _data[0];
		_data[0] = _data[_count - 1];
		--_count;

		//sort the remaining
		int min;
		for (int i = 0; i < _count >> 1; i = min)
		{
			int child1 = (i << 1) + 1;
			int child2 = child1 + 1;
			//http://graphics.stanford.edu/~seander/bithacks.html#IntegerMinOrMax
			//r = y ^ ((x ^ y) & -(x < y)); // min(x, y)
			//r = x ^ ((x ^ y) & -(x < y)); // max(x, y)
			min = _data[child1] < _data[child2] ? child1 : child2;

			if (_data[i] < _data[min]) return result; //we have found our spot
			T item = _data[i];
			_data[i] = _data[min];
			_data[min] = item;
		}

		return result;
	}
}
#endif