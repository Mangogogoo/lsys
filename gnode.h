#ifndef GNODE_H
#define	GNODE_H

template <typename T>
struct gnode {
    T value;
    gnode *prev;
};


#endif	/* GNODE_H */

