/************ P R O J E C T ****************
Course : TGD2251 Game Physics
Session: Trimester 1, 2016/17
ID and Name #1 : 1141123928 Muhammad Asyraf bin Ibrahim
Contacts #1 : 013-4642899 asyzruffz@gmail.com
Lecture Section : TC01
Tutorial Section: TC01
********************************************/

#ifndef CONTACT_LISTENER_2D_HPP
#define CONTACT_LISTENER_2D_HPP

#include <Box2D/Box2D.h>

class ContactListener2D : public b2ContactListener
{
public:

	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);

};

#endif // CONTACT_LISTENER_2D_HPP