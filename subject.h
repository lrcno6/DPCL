#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include<set>
#include<map>
#include<functional>
#include<thread>
#include<mutex>
#include<utility>
#include<cstdint>
#include"baseargument.h"
namespace dpcl{
	class Subject{
		public:
			mutex m_mutex;
			Subject()=default;
			Subject(const Subject&)=delete;
			Subject(Subject&&)=default;
			virtual ~Subject(){
				using namespace std;
				lock_guard<mutex> lock(m_mutex);
				for(auto i:m_atom_map)
					delete i.second.first;
			}
			Subject& operator=(const Subject&)=delete;
			Subject& operator=(Subject&&)=delete;
			template<typename return_type>
			uint64_t connect(uint32_t Signal,const std::function<return_type(const BaseArgument&)> &func){
				while(1){
					uint64_t atom=(uint64_t)rand()<<60^(uint64_t)rand()<<45^rand()<<30^rand()<<15^rand();
					if(!m_atom_map.count(atom)){
						m_atom_map[atom]=std::pair(new Function(func),atom);
						m_signal_map[Signal].insert(atom);
						return atom;
					}
				}
			}
			template<class type,typename return_type>
			uint64_t connect(uint32_t Signal,type &obj,return_type(type::*method)(const BaseArgument&)){
				while(1){
					uint64_t atom=(uint64_t)rand()<<60^(uint64_t)rand()<<45^rand()<<30^rand()<<15^rand();
					if(!m_atom_map.count(atom)){
						m_atom_map[atom]=std::pair(new Method(obj,method),atom);
						m_signal_map[Signal].insert(atom);
						return atom;
					}
				}
			}
			bool disconnect(uint64_t atom){
				if(m_atom_map.count(atom)){
					m_signal_map[m_atom_map[atom].second].erase(atom);
					delete m_atom_map[atom].first;
					m_atom_map.erase(atom);
					return true;
				}
				else
					return false;
			}
			// it will call the functions/methods serially
			void call(uint32_t Signal,const BaseArgument &arg){
				if(m_signal_map.count(Signal))
					for(auto i:m_signal_map[Signal])
						m_atom_map[i].first->call(arg);
			}
			// it will call the functions/methods in parallel
			void call_in_parallel(uint32_t Signal,const BaseArgument &arg){
				if(m_signal_map.count(Signal))
					for(auto i:m_signal_map[Signal]){
						std::thread T()
					}
						//m_atom_map[i].first->call(arg);
			}
		private:
			class Callable{
				public:
					Callable()=default;
					Callable(const Callable&)=delete;
					Callable(Callable&&)=default;
					virtual ~Callable()=default;
					Callable& operator=(const Callable&)=delete;
					Callable& operator=(Callable&&)=delete;
					virtual void call(const BaseArgument&)const=0;
			};
			template<typename return_type>
			class Function:public Callable{
				public:
					Function(const std::function<return_type(const BaseArgument&)> &func):m_func(func){}
					void call(const BaseArgument &arg)const{
						m_func(arg);
					}
				private:
					std::function<return_type(const BaseArgument&)> m_func;
			};
			template<class type,typename return_type>
			class Method:public Callable{
				public:
					Method(type &obj,void (type::*method)(const BaseArgument&)):m_obj(obj),m_method(method){}
					virtual void call(const BaseArgument &arg)const{
						(m_obj.*m_method)(arg);
					}
				private:
					type &m_obj;
					void (type::*m_method)(const BaseArgument&);
			};
			std::map<uint64_t,std::pair<Callable*,uint32_t>> m_atom_map;
			std::map<uint32_t,set<uint64_t>> m_signal_map;
	};
}
#endif