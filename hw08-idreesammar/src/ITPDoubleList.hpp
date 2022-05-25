// ITPDoubleList.hpp
// Defines and implements the ITPDoubleList collection

#pragma once
#include <ostream>
#include <sstream>
#include <stdexcept>

template <typename T>
class ITPDoubleList
{
private:
    
    // Node only used internally to list
    struct Node
    {
        // Data in this node
        T mData;
        // Link to previous node
        Node* mPrev;
        // Link to next node
        Node* mNext;
    };
    
    // Pointer to the head node
    Node* mHead;
    // Pointer to the tail node
    Node* mTail;
    // Number of nodes currently in the list
    unsigned mSize;
    
public:
    // Iterator helper class...
    class Iterator
    {
    private:
        Node* mCurr;
    public:
        // Needed for List access
        friend class ITPDoubleList;
        // Constructors
        Iterator()
        {
			// set to intial value
            mCurr = nullptr;
		}
        
        Iterator(Node* inCurr)
        {
            // set to input value
            mCurr = inCurr;
        }
        
        Iterator(const Iterator& src)
        {
            mCurr = src.mCurr; // set to input's member variables
        }
        
        // Assignment
        Iterator& operator=(const Iterator& src)
        {
            // set to input member variables
            mCurr = src.mCurr;

            return *this; // by convention
		}
        
        // Incrementors / Decrementors
        // ++i
        Iterator& operator++()
        {
			// increment the mCurr value
            mCurr = mCurr->mNext;

            return *this; // by convention
		}
        
        // i++
        Iterator operator++(int)
        {
            Iterator retval(*this);
            mCurr = mCurr->mNext; // set to next node

            return retval; // return retVal
        }
        
        // --i
        Iterator& operator--()
        {
            // set value to previous
            mCurr = mCurr->mPrev;

            return *this; // by convention
        }
        
        // i--
        Iterator operator--(int)
        {
            Iterator retval(*this);
            mCurr = mCurr->mPrev; // set to previous

            return retval; // return retVal
        }
        
        // Dereference
        T& operator*() const
        {
            // return the value of the node iterator points to
            return mCurr->mData; 
        }
        
        Node* operator->() const
        {
            // return the node that iterator points to
            return mCurr; 
        }
        
        // Comparison
        bool operator==(const Iterator& rhs) const
        {
            // comapre the values
            return (mCurr == rhs.mCurr); 
        }
        
        bool operator!=(const Iterator& rhs) const
        {
            // compare the values
            return (mCurr != rhs.mCurr);
        }
    };
    
    // List functions...
    
    // Function: Default Constructor
    // Purpose: Initializes size to 0 and head/tail to null
    // Input: None
    // Returns: Nothing
    ITPDoubleList()
    {
        // 1. Set size to 0
        mSize = 0; 
        // 2. Set head to null
        mHead = nullptr;
        // 3. Set tail to null
        mTail = nullptr;
    }
    
    // Function: Copy Constructor
    // Purpose: Initializes this list as a deep copy of other
    // Input: Other list to copy (const reference)
    // Returns: Nothing
    ITPDoubleList(const ITPDoubleList& other)
    {
        // 1. Set size to 0, head to null, tail to null
        mSize = 0;
        mHead = nullptr;
        mTail = nullptr;

        // 2. Create a temp that points to the head node in “other”
        struct Node* temp = other.mHead;


        // 3. While temp is not null…
        while (temp != nullptr)
        {
            push_back(temp->mData); // 1. push_back temp’s data into this list
            temp = temp->mNext; // 2. Advance temp to the next node
        }
    }
    
    // Function: Destructor
    // Purpose: Calls the clear function to delete the list
    // Input: None
    // Returns: Nothing
    ~ITPDoubleList()
    {
        // 1. Call the clear function!
        clear();
	}
    
    // Function: clear
    // Purpose: Deletes every node in this list, sets size to 0, and head/tail to null
    // Input: None
    // Returns: Nothing
    void clear()
    {
        // 1. While size > 0…
        while (mSize > 0)
        {
            pop_front(); // Call pop_front
        }
        // NOTE: this will eventually end up decrementing mSize to 0 plus setting head/tail to null
    }
    
    // Assignment Operator
    // Function: Assignment Operator
    // Purpose: Clear this list, and then make a deep copy of other
    // Input: Other list to copy (const reference)
    // Returns: *this
    ITPDoubleList& operator=(const ITPDoubleList& other)
    {
        // 1. Call clear (to clear out any values already in this list)
        clear();

        // 2. Create a temp that points to the head node in “other”
        struct Node* temp = other.mHead;

        // 3. While temp is not null…
        while (temp != nullptr)
        {
            push_back(temp->mData);// push_back temp’s data into this list
            temp = temp->mNext; // Advance temp to the next node
        }
            
        // 4. By convention, operator= returns *this
        return *this; 
    }
    
    // Function: size
    // Purpose: Gets the current size of the linked list
    // Input: None
    // Returns: size of the list
    unsigned size() const
    {
        // gets current size of linked list
        return mSize;     
    }
    
    // Function: push_front
    // Purpose: Inserts a node at the front of the linked list
    // Input: Value to store in the new node
    // Returns: Nothing
    void push_front(const T& value)
    {
        // 1. Dynamically allocate a new node
        struct Node* n = new Node();
        n->mData = value; // Set its data to the value
        n->mPrev = nullptr; // Set its previous to null (since this will be the new head)
        n->mNext = mHead; // Set its next to the current head

        // 2. If the size is 0…The tail is the new node
        if (mSize == 0)
        {
            mTail = n; // tail is the new node
        }

        // 3. Otherwise…set the previous of the current head to the new node
        else  // mSize is not 0
        { 
            mHead->mPrev = n;
        }

        // 4. Set the head to the new node
        mHead = n;

        // 5. Increment the size
        mSize++;
    }
    
    // Function: front
    // Purpose: Gets the value of the node at the front of the list
    // Input: None
    // Returns: Value of the node at the front of the list
    T& front()
    {
        // 1. If the size is 0, error!
        if (mSize == 0)
        {
            throw std::out_of_range("Error: no elements currently in list!");
        }

        // 2. Return the data at the head node
        return mHead->mData;    
    }
    
    // Function: pop_front
    // Purpose: Removes the node at the front of the list
    // Input: None
    // Returns: None
    void pop_front()
    {
        // 1. If the size is 0 … error!
        if (mSize == 0)
        {
            throw std::out_of_range("Error: no elements currently in list!");
        }

        // 2. Otherwise if the size is 1…
        else if (mSize == 1)
        {
            delete mHead; // Delete the head node

            // Set head and tail to null, size to 0
            mHead = nullptr;
            mTail = nullptr;
            mSize = 0;
        }

        // 3. Otherwise…
        else 
        {
            struct Node* temp = mHead->mNext; // 1. Set a temp equal to the next node after head
            delete mHead; // 2. Delete the head node
            mHead = temp; // 3. The new head is temp
            mHead->mPrev = nullptr; // 4. The new head previous is now null
            mSize--; // 5. Decrement size
        }
           
    }
    
    // Function: push_back
    // Purpose: Inserts a node at the end of the linked list
    // Input: Value to store in the new node
    // Returns: Nothing
    void push_back(const T& value)
    {
        // 1. Dynamically allocate a new node
        struct Node* n = new Node();
        n->mData = value; // Set its data to the value
        n->mPrev = mTail; // Set its previous to the current tail
        n->mNext = nullptr; // Set the next to null (since this will be the new tail)

        // 2. If the size is 0…The head is the new node
        if (mSize == 0)
        {
            mHead = n; // head is the new node
        }

        // 3. Otherwise…set the next of the current tail to the new node
        else  // mSize is not 0
        {
            mTail->mNext = n;
        }

        // 4. Set the tail to the new node
        mTail = n;

        // 5. Increment the size
        mSize++;

    }
    
    // Function: back
    // Purpose: Gets the value of the node at the back of the list
    // Input: None
    // Returns: Value of the node at the back of the list
    T& back()
    {
        // 1. If the size is 0, error!
        if (mSize == 0)
        {
            throw std::out_of_range("Error: no elements currently in list!");
        }

        // 2. Return the data at the tail node
        return mTail->mData;    
    }

    // Function: pop_back
    // Purpose: Removes the node at the end of the list
    // Input: None
    // Returns: None
    void pop_back()
    {
        // 1. If the size is 0 … error!
        if (mSize == 0)
        {
            throw std::out_of_range("Error: no elements currently in list!");
        }

        // 2. Otherwise if the size is 1…
        else if (mSize == 1)
        {
            delete mTail; // Delete the tail node

            // Set head and tail to null, size to 0
            mHead = nullptr;
            mTail = nullptr;
            mSize = 0;
        }

        // 3. Otherwise…
        else
        {
            struct Node* temp = mTail->mPrev; // 1. Set a temp equal to the previous node before the tail
            delete mTail; // 2. Delete the tail node
            mTail = temp; // 3. The new tail is temp
            mTail->mNext = nullptr; // 4. The new tail next is now null
            mSize--; // 5. Decrement size
        }
    }
    
    // Function: begin
    // Purpose: Gets an iterator for the start of the list
    // Input: None
    // Returns: Iterator pointing to beginning of list
    Iterator begin() const
    {
        // return iterator pointing to start of list
        Iterator it(mHead);
        return it; 
    }
    
    // Function: end
    // Purpose: Gets an iterator for the end of the list
    // Input: None
    // Returns: Iterator pointing to end of list
    Iterator end() const
    {
        // return iterator pointing to end of list (the tails next which is one after last element)
        Iterator it(mTail->mNext);
        return it; 
    }

	// Function: erase
	// Purpose: Removes the item at the node pointed to by i
	// Input: Iterator pointing to a valid node to remove before
	// Returns: A new iterator pointing to the node after the removed item
    Iterator erase(Iterator& i)
    {
        // 1. If the iterator is invalid … error!
        if (i.mCurr == nullptr) // this means i points to null (therefor is invalid)  
        {
            throw std::out_of_range("Error: the iterator is out of range!");
        }
        // 2. If the iterator is at begin
        if (i == begin())
        {
            pop_front(); // 1. pop_front
            return begin(); // 2. Return begin
        }
        // 3. If the iterator is at the tail
        if (i.mCurr == mTail)
        {
            pop_back(); // 1. pop_back
            return end(); // 2. Return end
        }
        // 4. Otherwise...
        else
        {
            // 1. Make “before”, “after”, and “toDel” pointers
            struct Node* before = i->mPrev;
            struct Node* after = i->mNext;
            struct Node* toDel = i.mCurr;

            Iterator retVal = i; // stores iterator to next address (needs this because current iterator node about to be deleted)
            retVal++; // get that next address/node

            // 2. Delete “toDel”
            delete toDel;

            // 3. Set before’s next to after
            before->mNext = after; 
            // 4. Set after’s previous to before
            after->mPrev = before; 

            // 5. Decrement size
            mSize--; 

            // 6. Return an iterator to after
            return retVal; // essentially i++ for original i
        }
    }

	// Function: insert
	// Purpose: Inserts a list item before node pointed to by i
	// Input: Iterator pointing to a valid node to insert before
	// Returns: A new iterator pointing to the inserted value
    Iterator insert(Iterator& i, const T& val)
    {
        // 1. If the iterator is invalid … error!
        if (i.mCurr == nullptr) // this means i points to null (therefor is invalid)  
        {
            throw std::out_of_range("Error: the iterator is out of range!");
        }
        // 2. If the iterator is at begin
        if (i == begin())
        {
            push_front(val); // push_front
            return begin(); // return begin
        }
        // 3. If the iterator is at end
        if (i == end())
        {
            push_back(val); // push_back

            // Return iterator to last element (not end!)
            Iterator retVal = i;
            retVal--; // one before the end
            return retVal; // return the last element
        }
        // 4. Otherwise…
        else
        {
            // 1. Make “before” and “after” pointers
            struct Node* before = i->mPrev;
            struct Node* after = i.mCurr; // the current node will be the after to the inserted node

            // 2. Dynamically allocate a new node
            struct Node* n = new Node();
            n->mData = val; // a) Set its data to the value
            n->mPrev = before; // b) Set its previous to before
            n->mNext = after; // c) Set its next to after

            // 3. Set before’s next to the new node
            before->mNext = n; 
            // 4. Set after’s previous to the new node
            after->mPrev = n;

            // 5. Increment size
            mSize++; 

            // 6. Return an iterator pointing to the inserted node
            Iterator retVal = i;
            retVal--; // points to node inserted before given i
            return retVal; 
        }
    }
    
public:
    // Function: Output Stream Operator
    // Purpose: Prints the contents of the list to the provided stream
    // Written in the format of {x, y, ..., z}
    // Input: Stream to write to, list to write
    // Output: Stream after values are written
    friend std::ostream& operator<<(std::ostream& os, const ITPDoubleList<T>& list)
    {       
        // Create a pointer variable (temp) that stores the address of the head node 
        struct Node* temp = list.mHead;
        
        os << "{"; // output starting brace

        // While temp != nullptr…
        while (temp != nullptr)
        {
            os << temp->mData; // Output the data for the “temp” node

            if (temp != list.mTail)  // for nodes that are not the last
            {
                os << ","; // output comma and space
            }
           
            temp = temp->mNext; // Update the temp node to be the next link
        }

        os << "}"; // output end brace 
        
        return os; // return output stream
    }
    
    // Function: toString
    // Purpose: Converts list to a string
    // Input: None
    // Output: String (in the format as the ostream)
    std::string toString() const
    {
        std::ostringstream oss; // stream that will obtain output

        // obtain output using << operator
        oss << *this;

        std::string content = oss.str(); // string to hold oss output
        return content; 
    }
    
    // Function: toReverseString
    // Purpose: Outputs the list in reverse
    // Input: None
    // Output: String in reverse
    std::string toReverseString() const
    {
        std::ostringstream os; // stream that will obtain output
        
        // Create a pointer variable (temp) that stores the address of the tail node 
        struct Node* temp = this->mTail;

        os << "{"; // output starting brace

        // While temp != nullptr…
        while (temp != nullptr)
        {
            os << temp->mData; // Output the data for the “temp” node

            if (temp != this->mHead)  // for nodes that are not the first
            {
                os << ","; // output comma and space
            }

            temp = temp->mPrev; // Update the temp node to be the previous link
        }

        os << "}"; // output end brace 

        std::string content = os.str(); // string to hold oss output

        return content; // return value
    }
};
