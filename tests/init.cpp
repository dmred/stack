#include "stack.hpp"
#include <catch.hpp>
#include <iostream>
#include <thread>
#include<mutex>
using namespace std;

SCENARIO("count", "[count]"){
  stack<int> s;
  s.push(1);
  REQUIRE(s.count()==1);
}

SCENARIO("push", "[push]"){
  stack<int> s;
  s.push(1);
  REQUIRE(s.count()==1);

}

/*SCENARIO("top", "[top]"){
  stack<int> s;
  s.push(1);
  s.push(2);
  s.push(3);
  s.pop();

  REQUIRE(s.top()==2);
}*/

SCENARIO("empty", "[empty]"){
  stack<int> s;
  s.push(1);
  REQUIRE(s.empty()==false);
}
/*
SCENARIO("empty2", "[empty2]"){
  stack<int> s;
  s.push(1);
  s.top();
  s.pop();
  REQUIRE(s.empty()==true);
}

SCENARIO("empty3", "[empty3]"){
  stack<int> s;
  s.push(1);
  s.push(2);
  s.top();
  s.pop();
  
  
  REQUIRE(s.empty()==false);
}
*/
SCENARIO("threads", "[threads]"){
  stack<int> s;
  s.push(1);
  s.push(2);
  s.push(3);
	std::thread t1([&s](){
		for (int i = 0; i < 5; i++) {
			s.push(i + 4);
		}
	});
	std::thread t2([&s](){
		for (int i = 0; i < 5; i++)
		{
			s.pop();
		}
	});
	t1.join();
	t2.join();
  REQUIRE(s.count()==3);
}

/*
SCENARIO("thread", "[thread]"){
  stack<int> s;
  s.push(3);
  s.push(2);
  s.push(1);
	std::thread t1([&s](){
		for (int i = 0; i < 5; i++) {
			s.push(i + 4);
		}
	});
	std::thread t2([&s](){
		for (int i = 0; i < 5; i++)
		{
			s.pop();
		}
	});
	t1.join();
	t2.join();
  REQUIRE(s.count()==3);
}

*/
/*
SCENARIO("operprisv", "[operprisv]"){
  stack<int> s1;
  s1.push(1);
  stack<int> s2;
  s2=s1;
  REQUIRE(s1.count()==s2.count());
}

SCENARIO("const", "[constr]"){
  stack<int> s1;
  s1.push(1);
  stack<int> s2=s1;
  REQUIRE(s1.count()==s2.count());
}
*/
