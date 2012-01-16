
#ifndef __DeckGUI_H
#define __DeckGUI_H
#include <gdkmm/pixbuf.h>
#include <vector>
#include "Card.h"
using std::vector;


class DeckGUI {
public:
	DeckGUI();
	virtual ~DeckGUI();
	Glib::RefPtr<Gdk::Pixbuf> getCardImage( Rank f, Suit s );   // Returns the image for the specified card.
	Glib::RefPtr<Gdk::Pixbuf> getNullCardImage();                 // Returns the image to use for the placeholder.

private:
	vector< Glib::RefPtr< Gdk::Pixbuf > > deck;                   // Contains the pixel buffer images.
}; // DeckGUI
#endif
