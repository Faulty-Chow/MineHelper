#ifndef _TWODIMENSIONARRAY_H
#define _TWODIMENSIONARRAY_H

#include <iostream> 
#include <memory>

using namespace std;

template<class T>
class Array2D{
private:
	shared_ptr<long> m_count;
	shared_ptr<int> m_height;
	shared_ptr<int> m_width;
	T** m_value;
public:
	Array2D(const Array2D &_rhs)
		:m_width(_rhs.m_width)
		,m_height(_rhs.m_height)
		,m_value(_rhs.m_value)
		,m_count(_rhs.m_count){
			if(*m_count!=0)
				++(*m_count);
	}
	Array2D(){
		m_width=shared_ptr<int>(new int(0));
		m_height=shared_ptr<int>(new int(0));
		m_count=shared_ptr<long>(new long(0));
		//cout<<"construct\n";
	}
	Array2D(int _width,int _height){
		m_width=shared_ptr<int>(new int(_width));
		m_height=shared_ptr<int>(new int(_height));
		m_value=new T *[_height];   //如果这里用new T*[_width]那么在取值时即可x,y正序
		m_count=shared_ptr<long>(new long(1));
		for (int j=0;j<_height;++j){
			m_value[j]=new T[_width];
		}
		//cout <<"w,h\n";
	}
	Array2D& operator=(const Array2D &_r){
		//cout<<"==\n";
		if(this==&_r)
			return *this;
		dispose();
		m_value=_r.m_value;
		m_width=_r.m_width;
		m_height=_r.m_height;
		m_count=_r.m_count;
		if(*m_count!=0)
			++(*m_count);
		return *this;
	}

	const T& GetValue(const  int x,const int y) const{
		if(!IsInArray(x,y)){
			//boost::format fmt("%1%,%2%");
			//fmt % x % y;
			////string str=boost::lexical_cast<string>(x) 
			//throw std::out_of_range(fmt.str());
			//ASSERT(0);
			throw;
		}
		return m_value[y][x];
	}
	T& GetValue(const  int x,const int y){
		if(!IsInArray(x,y)){
			throw;
		}
		return m_value[y][x];
	}
	const int GetWidth() const {return *m_width;}
	const int GetHeight() const {return *m_height;}
	void SetAllValue(const T &_value)   //N次在这个函数上栽跟头,开始这个函数名为SetValue(与下面的相同)，当在循环中给每一项赋值时，本来应该是twoD.SetValue(i,j,value)，而经常会写成twoD.SetValue(value) 
	{
		for (int j=0;j<*m_height;++j){
			for (int i=0;i<*m_width;++i){
				m_value[j][i]=_value;
			}
		}
	}
	void SetValue(int x,int y,const T &_value){
		if(!IsInArray(x,y)){
			throw;
		}
		m_value[y][x]=_value;
	}
	Array2D<T> DeepClone() const {
		Array2D<T> r(*m_width,*m_height);
		for (int j=0;j<*m_height;++j){
			for (int i=0;i<*m_width;++i){
				r.m_value[j][i]=m_value[j][i];
			}
		}
		return r;
	}
	~Array2D(){
		dispose();
		//cout <<"Dispose\n";
	}

	void dispose(){
		if(*m_count==0)
			return;
		--(*m_count);
		if(*m_count==0){
			for (int j=0;j<*m_height;++j){
				//这里必须加[]，在有些情况下只能用delete[] 
				delete[] m_value[j];
			}
			//                 if(m_height!=0)
			//                 {
			delete[] m_value;
			/*} */
		}
	}
	bool IsInArray(int x, int y){
		if(x >=0 && x < *m_width && y >=0 && y < *m_height){
			return true;
		}else{
			return false;
		}
	}
};


#endif


