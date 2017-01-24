/**********************************
 * FILE NAME: Member.h
 *
 * DESCRIPTION: Definition of all Member related class
 **********************************/

#ifndef MEMBER_H_
#define MEMBER_H_

#include "stdincludes.h"

/**
 * CLASS NAME: q_elt
 *
 * DESCRIPTION: Entry in the queue
 */
class q_elt {
public:
	void *elt;
	int size;
	q_elt(void *elt, int size);
};

/**
 * CLASS NAME: Address
 *
 * DESCRIPTION: Class representing the address of a single node
 */
class Address {
public:
	char addr[6];

    // Default constructor
	Address() {}

	// Copy constructor
	Address(const Address &anotherAddress);

	 // Overloaded = operator
	Address& operator =(const Address &anotherAddress);

    // Overloaded == operator
	bool operator ==(const Address &anotherAddress);

    // constructor from a string in the format "id:port"
    // and store them into a char array addr
	Address(string address) {
		size_t pos = address.find(":");
		int id = stoi(address.substr(0, pos));
		short port = (short)stoi(address.substr(pos + 1, address.size()-pos-1));
		memcpy(&addr[0], &id, sizeof(int));
		memcpy(&addr[4], &port, sizeof(short));
	}

    // convert address into a string in the form id:port
	string getAddress() {
		int id = 0;
		short port;
		memcpy(&id, &addr[0], sizeof(int));
		memcpy(&port, &addr[4], sizeof(short));
		return to_string(id) + ":" + to_string(port);
	}

	void init() {
		memset(&addr, 0, sizeof(addr));
	}
};

/**
 * CLASS NAME: MemberListEntry
 *
 * DESCRIPTION: Entry in the membership list
 */
class MemberListEntry {
public:
	int id;
	short port;
	long heartbeat;
	long timestamp;

    // constructors
	MemberListEntry(int id, short port, long heartbeat, long timestamp);
	MemberListEntry(int id, short port);
	MemberListEntry(): id(0), port(0), heartbeat(0), timestamp(0) {}
	MemberListEntry(const MemberListEntry &anotherMLE);
	MemberListEntry& operator =(const MemberListEntry &anotherMLE);

    // getters
	int getid();
	short getport();
	long getheartbeat();
	long gettimestamp();

    // setters
	void setid(int id);
	void setport(short port);
	void setheartbeat(long hearbeat);
	void settimestamp(long timestamp);
};

/**
 * CLASS NAME: Member
 *
 * DESCRIPTION: Class representing a member in the distributed system
 */
// Declaration and definition here
class Member {
public:
	Address addr;

	bool inited; 
	bool inGroup;  // boolean indicating if this member is in the group;
	bool bFailed; // boolean indicating if this member has failed

	int nnb;            // number of my neighbors
	long heartbeat;     // the node's own heartbeat
	int pingCounter;    // counter for next ping
	int timeOutCounter; // counter for ping timeout

	vector<MemberListEntry> memberList;      // Membership table
	vector<MemberListEntry>::iterator myPos; // My position in the membership table

	queue<q_elt> mp1q; // Queue for failure detection messages

	/**
	 * Constructor
	 */
	Member(): inited(false), inGroup(false), bFailed(false), nnb(0), heartbeat(0), pingCounter(0), timeOutCounter(0) {}
	// copy constructor
	Member(const Member &anotherMember);
	// Assignment operator overloading
	Member& operator =(const Member &anotherMember);
	virtual ~Member() {}
};

#endif /* MEMBER_H_ */
