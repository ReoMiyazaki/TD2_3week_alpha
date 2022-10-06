#include"Input.h"

bool Input::ReleaseKey(BYTE keyNumber)const {
	return (keyPre_[keyNumber] && !key_[keyNumber]);
}