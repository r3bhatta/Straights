#ifndef SubjectGUI_H
#define SubjectGUI_H

#include <set>

class ObserverGUI;

class SubjectGUI {
public:
       void subscribe( ObserverGUI* );
       void unsubscribe( ObserverGUI* );

protected:
       void notify();

private:
       typedef std::set< ObserverGUI* > Observers;
       Observers observers_;
};

#endif
