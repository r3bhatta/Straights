#include"SubjectGUI.h"
#include <set>
#include"ObserverGUI.h"

void SubjectGUI::notify() {
    Observers::iterator i;
    for (i = observers_.begin(); i != observers_.end(); ++i)
        (*i)->update();
}

void SubjectGUI::subscribe (ObserverGUI *newView) {
    observers_.insert(newView);
}

void SubjectGUI::unsubscribe (ObserverGUI *formerView) {
    observers_.erase(formerView);
}
