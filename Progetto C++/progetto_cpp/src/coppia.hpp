
#ifndef COPPIA_HPP_
#define COPPIA_HPP_

template <typename P, typename S>
class Coppia {
	P primo;
	S secondo;
public:
	Coppia(P p, S s): primo(p), secondo(s) {}
	P getPrimo() {return primo;}
	S getSecondo() {return secondo;}
	void setPrimo(P p) {primo = p;}
	void setSecondo(S s) {secondo = s;}
	~Coppia() {}
};

#endif /* COPPIA_HPP_ */
