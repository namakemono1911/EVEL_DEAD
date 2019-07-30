/*****************************************************************************
convenient.h
Aythor	: ���@��
Data	: 2017_08_18
=============================================================================
Updata

*****************************************************************************/
#ifndef CONVENIENT_H
#define	CONVENIENT_H
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include <string>
#include <list>
#include <vector>

//////////////////////////////////////////////////////////////////////////////
//�N���X��`
//////////////////////////////////////////////////////////////////////////////
class Transform;

class Conveni
{
public:
	Conveni(){}
	~Conveni(){}

	static list<string>	getDirFile(const string dirName, const string ext);
	static int			getCharPosition(const string str, const string target);

	static Dmtx setMatrix(Dvec3 pos, Dvec3 rot, Dvec3 size);
	static Dmtx setMatrix(Transform trans);
	static Dmtx setQuatenionMatrix(Dvec3 pos, Dvec3 quatenion, Dvec3 size);

private:

};

#endif // !CONVENIENT_H
