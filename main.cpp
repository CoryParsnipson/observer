#include <string>
#include <iostream>
#include "Observer.h"

class TestSubject : public Subject<std::string> {
public:
   TestSubject(std::string id) : Subject(id) {}

   void do_notify() {
      this->notify(this->id_);
   }
};

class Test : public Observer<std::string> {
public:
   Test(std::string id) : Observer(id) {}

   virtual void notify(std::string& message) {
      std::cout << *this << " " << message << " Poop." << std::endl;
   }
};

int main() {
   TestSubject s("s");
   TestSubject s2("s2");
   std::vector<Test*> t;

   std::cout << "Creating subject - " << s << std::endl;

   for (int i = 0; i < 5; ++i) {
      t.push_back(new Test("Observer #" + std::to_string(i + 1)));
      s.attach(*t[i]);
   }

   s.do_notify();

   std::cout << "=========================" << std::endl;

   // detach an observer and see what happens.
   s.detach(*t[2]);
   s.do_notify();

   std::cout << "=========================" << std::endl;

   // delete an observer without detaching it and see what happnens
   delete t[3];
   t.erase(t.begin() + 3);

   s.do_notify();

   std::cout << "=========================" << std::endl;

   // attach a second observer
   for (int i = 0; i < 5; ++i) {
      s2.attach(*t[i]);
   }

   s.do_notify();
   s2.do_notify();

   std::cout << "=========================" << std::endl;

   // delete another observer
   
   delete t[3];
   t.erase(t.begin() + 3);

   s.do_notify();
   s2.do_notify();

   std::vector<Test*>::const_iterator it;
   for (it = t.begin(); it != t.end(); ++it) {
      delete *it;
   }
   t.clear();

   return 0;
}
