#pragma once

#include<DxLib.h>
#include<cassert>
#include<algorithm>
#include"../main/config.h"

namespace DxLib {
	struct Vec2 {
		int x=0, y=0;

		static Vec2 zero() { return Vec2{ 0,0 }; }
		operator VECTOR () {
			return VGet(x,y,0);
		}
		
		Vec2 operator +(const Vec2& a) {return Vec2{ this->x + a.x,this->y + a.y };		}
		Vec2 operator -(const Vec2& a) {return Vec2{ this->x - a.x,this->y - a.y };		}
		Vec2 operator *(const Vec2& a) {return Vec2{ this->x * a.x,this->y * a.y };		}
		Vec2 operator /(const Vec2& a) {return Vec2{ this->x / a.x,this->y / a.y };		}
		Vec2 operator %(const Vec2& a) {return Vec2{ this->x % a.x,this->y % a.y };		}
		const Vec2& operator +=(const Vec2& a) {
			this->x += a.x;
			this->y += a.y;
			return (*this);
		}
		const Vec2& operator -=(const Vec2& a) {
			this->x -= a.x;
			this->y -= a.y;
			return (*this);
		}
		const Vec2& operator *=(const Vec2& a) {
			this->x *= a.x;
			this->y *= a.y;
			return (*this);
		}
		const Vec2& operator /=(const Vec2& a) {
			this->x /= a.x;
			this->y /= a.y;
			return (*this);
		}
		const Vec2& operator %=(const Vec2& a) {
			this->x %= a.x;
			this->y %= a.y;
			return (*this);
		}
		const bool operator ==(const Vec2& a) {return ((this->x == a.x) && (this->y == a.y));}

		Vec2 operator -(const VECTOR& a) {return (*this) - Vec2{ (int)a.x,(int)a.y };}

	};

	struct Rect {
		Rect(float x, float y, float sx, float sy)
			:posX(x)
			, posY(y)
			, sizeX(sx)
			, sizeY(sy)
		{}

		float posX;
		float posY;
		float sizeX;
		float sizeY;
	};

	//ŽlŠp“–‚½‚è”»’è
	inline bool SquareCollision(Rect a, Rect b) {
		if (a.posY >= b.posY + b.sizeY)
			return false;//up
		if (a.posY + a.sizeY <= b.posY)
			return false;//down

		if (a.posX >= b.posX + b.sizeX)
			return false;//left
		if (a.posX + a.sizeX <= b.posX)
			return false;//right


		return true;
	}

	inline bool SquareCollision(const VECTOR& posa, const VECTOR& sizea, const VECTOR& posb, const VECTOR& sizeb) {
		Rect a=Rect(posa.x,posa.y,sizea.x,sizea.y);
		Rect b=Rect(posb.x,posb.y,sizeb.x,sizeb.y);

		return SquareCollision(a,b);
	}

	inline VECTOR VGet(const Vec2& value) {
		return VGet((float)value.x,(float)value.y,0);
	}

	inline VECTOR operator *(const VECTOR& a, const VECTOR& b) {
		return VGet(a.x * b.x, a.y * b.y, a.z * b.z);
	}
	inline VECTOR& operator *=(VECTOR& a, const VECTOR& b) {
		return a=a*b;
	}
}