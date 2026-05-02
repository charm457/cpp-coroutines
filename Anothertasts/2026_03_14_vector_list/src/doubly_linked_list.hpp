#pragma once

#include <cstddef>

namespace bdk {
	template <typename T> 
	class DoublyLinkedList {
		private:
			class Node {
				public:
					T value;
					Node* prev = nullptr;
					Node* next = nullptr;
					
					Node(const T& value) : value(value) {}
						
					Node(const Node&) = delete;
					Node& operator = (const Node&) = delete;
			};

			Node* begin = nullptr;
			Node* end = nullptr;
			std::size_t size = 0;

		public:
			DoublyLinkedList() noexcept = default;
			DoublyLinkedList(const DoublyLinkedList&) = delete;
			DoublyLinkedList& operator = (const DoublyLinkedList&) = delete;
			~DoublyLinkedList();
			
			std::size_t get_size() const noexcept;
			bool has_item(const T& value) const noexcept;
			void print() const noexcept;
			bool insert(std::size_t position, const T& value);
			void push_back(const T& value);
			bool remove_first(const T& value) noexcept;
	};
}