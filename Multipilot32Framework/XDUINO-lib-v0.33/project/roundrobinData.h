/******************************************************************
*  Copyright (C) 2009 Ram Narula <ram@pluslab.com> 
*  Filename: roundrobinData.h
*  Version: 0.3
*  Date: 05 August 2009
*  Information: http://www.xduino.com/    
******************************************************************/
/******************************************************************
*   This file is part of XDUINO-lib
*
*   XDUINO-lib is free software: you can redistribute it and/or modify
*   it under the terms of the GNU Lesser General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*	
*   XDUINO-lib is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU Lesser General Public License for more details.
*
*   You should have received a copy of the GNU Lesser General Public License
*   along with XDUINO-lib.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************/
// load this library only once
#ifndef roundrobinData_h
#define roundrobinData_h


// get array size *
//template<typename T, int size>
//int ARRAYSIZE(T(&)[size]){return size;}

template <typename T>
class RoundRobinData {

		public:
		// variables
			
		// methods
			RoundRobinData(T * s_,int size_);
			T Get(void);
			T Put(T c);
			bool notEmpty(void);
			bool isFull(void);
			void Reset(void);

			
			
		private:
		// variables
			
			T * s;
			T * volatile current;
			T * volatile start;
			int size;
			bool full;
						
		// methods
			T * Next(T *p);
};


template <class T>
RoundRobinData<T>::RoundRobinData(T * s_,int size_): s(s_),size(size_) {
		current=&s[0];
		start=&s[0];
		full=0;
}

template <class T>
T RoundRobinData<T>::Get(void) {
        T c=*start;
        if((start==current) && !(full)) // if not full but start==current means empty
					return 0;		
        
		
		// full means current was not shifted so shift it now as start will shift
		if(full) {
                full=0;
                current=Next(current);
        }

        
		start=Next(start);				// shift start normally
	
        return(c);
}

template <class T>
T RoundRobinData<T>::Put(T c) {
if(!full)		   						// if not full
{										// put c in current
        *current=c;

        if (Next(current) == start)		// if next is start means full
        {
                full=1;					// just mark full without shifting current
        } else {
                current=Next(current);	// normal case just shift current
                full=0;					// not full 
        }
        return c;

} else { 
		return 0; 						// do nothing if full
}

}

template <class T>
bool RoundRobinData<T>::notEmpty(void) {
		if(current==start) {
			return 0;
		} else {
			return 1;
		}
}

template <class T>
bool RoundRobinData<T>::isFull(void) {
		return full;
}

template <class T>
void RoundRobinData<T>::Reset(void) {
		full=0;
		current=&s[0];
		start=&s[0];
}

template <class T>
T * RoundRobinData<T>::Next(T *p) {
        T *q;
        q=p;
        if(q!=&s[size-1]) {q++;} else {q=&s[0];}	// if next is last then use first one
        return q;
}



#endif
