/*****************************************************************************
convenient.h
Aythor	: 上野　匠
Data	: 2017_08_18
=============================================================================
Updata

*****************************************************************************/
#ifndef CONVENIENT_H
#define	CONVENIENT_H
//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include <string>
#include <list>
#include <vector>

//////////////////////////////////////////////////////////////////////////////
//クラス定義
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
