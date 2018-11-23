#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include<string>
#include<map>
#include<set>
#include<functional>
#include<windows.h>
#include"rand.h"
namespace dpcl{
	class Subject{
		public:
			Subject()=default;
			Subject(const Subject&)=delete;
			virtual ~Subject(){
				for(auto i:m_call_map)
					for(auto j:i.second)
						delete j.second;
			}
			Subject& operator=(const Subject&)=delete;
			Subject& operator=(Subject&&)=delete;
			uint64_t connect(unsigned msg,std::function<void(WPARAM,LPARAM)> func){
				while(1){
					uint64_t atom=(uint64_t)Rand::rand()<<60|(uint64_t)Rand::rand()<<45|(uint64_t)Rand::rand()<<30|(uint64_t)Rand::rand()<<15|(uint64_t)Rand::rand();
					if(!m_msg_map.count(atom)){
						m_msg_map[atom]=msg;
						m_call_map[msg][atom]=new Function(func);
						return atom;
					}
				}
			}
			template<class type>
			uint64_t connect(unsigned msg,type &obj,void (type::*method)(WPARAM,LPARAM)){
				while(1){
					uint64_t atom=(uint64_t)Rand::rand()<<60|(uint64_t)Rand::rand()<<45|(uint64_t)Rand::rand()<<30|(uint64_t)Rand::rand()<<15|(uint64_t)Rand::rand();
					if(!m_msg_map.count(atom)){
						m_msg_map[atom]=msg;
						m_call_map[msg][atom]=new Method<type>(obj,method);
						return atom;
					}
				}
			}
			void disconnect(uint64_t atom){
				if(m_msg_map.count(atom)){
					delete m_call_map[m_msg_map[atom]][atom];
					m_call_map[m_msg_map[atom]].erase(atom);
					m_msg_map.erase(atom);
				}
				else
					throw std::string("Subject::disconnect:not found");
			}
			void call(unsigned msg,WPARAM wparam,LPARAM lparam){
				try{
					for(auto i:m_call_map.at(msg))
						i.second->call(wparam,lparam);
				}
				catch(std::out_of_range&){}
			}
		private:
			class Callable{
				public:
					Callable()=default;
					Callable(const Callable&)=delete;
					virtual ~Callable()=default;
					Callable& operator=(const Callable&)=delete;
					virtual void call(WPARAM,LPARAM)const=0;
			};
			class Function:public Callable{
				public:
					Function(std::function<void(WPARAM,LPARAM)> func):m_func(func){}
					virtual void call(WPARAM wparam,LPARAM lparam)const{
						m_func(wparam,lparam);
					}
				private:
					std::function<void(WPARAM,LPARAM)> m_func;
			};
			template<class type>
			class Method:public Callable{
				public:
					Method(type &obj,void (type::*method)(WPARAM,LPARAM)):m_obj(obj),m_method(method){}
					virtual void call(WPARAM wparam,LPARAM lparam)const{
						(m_obj.*m_method)(wparam,lparam);
					}
				private:
					type &m_obj;
					void (type::*m_method)(WPARAM,LPARAM);
			};
			std::map<unsigned,std::map<uint64_t,Callable*>> m_call_map;
			std::map<uint64_t,unsigned> m_msg_map;
	};
}
#endif