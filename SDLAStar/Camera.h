#pragma once
#include "BasicTypes.h"
#include <math.h>
class Camera
{
public:
	Camera(void);
	virtual ~Camera(void);
	inline void	set_zoom(const float zoom) { _zoom = zoom; }
	inline float	get_zoom()const { return _zoom; }
	//glm::mat3	get_transformation();

protected:
	void recreate_tranformation_matrix();

	struct Transformation
	{
		//Matrix       _matrix;
		Point2D     _last_pos;
		float        _last_zoom;
		Point2D     _last_origin;
		float        _last_rotation;
		void update(const Point2D& p, const Point2D& origin, const float zoom, const float rotation)
		{
			_last_pos = p; _last_origin = origin; _last_zoom = zoom; _last_rotation = rotation;
		}
	};

	float		_zoom;
	Transformation  _transform;

public:
	Point2D	_pos;
	Point2D	_origin;
	float		_rotation;
};

