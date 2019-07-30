#####################################################
# モデルリスト
#####################################################
PARTS_NAME zombie_body001.x
PARTS_NAME zombie_bottom_body001.x
PARTS_NAME zombie_head001.x
PARTS_NAME zombie_left_elbow.x
PARTS_NAME zombie_left_hand001.x
PARTS_NAME zombie_left_shin.x
PARTS_NAME zombie_left_shoes.x
PARTS_NAME zombie_left_shoulder001.x
PARTS_NAME zombie_left_thigh001.x
PARTS_NAME zombie_right_elbow.x
PARTS_NAME zombie_right_hand001.x
PARTS_NAME zombie_right_shin.x
PARTS_NAME zombie_right_shoes.x
PARTS_NAME zombie_right_shoulder001.x
PARTS_NAME zombie_right_thigh001.x
#####################################################
# モデル情報
#####################################################
SET_MODEL zombie_body001.x
{
	parent	= NULL
	pos		= 0.000000 8.420000 0.000000
	rot		= 0.000000 0.000000 0.000000
	size	= 1.000000 1.000000 1.000000
COLLISION_BOX
{
	pos		= 0.000000 2.600000 0.000000
	rot		= 0.000000 0.000000 0.000000
	size	= 4.090000 5.740000 1.780000
}
}
SET_MODEL zombie_bottom_body001.x
{
	parent	= zombie_body001.x
	pos		= 0.000000 0.000000 0.000000
	rot		= 0.000000 0.000000 0.000000
	size	= 1.000000 1.000000 1.000000
COLLISION_BOX
{
	pos		= 0.000000 -1.480000 0.000000
	rot		= 0.000000 0.000000 0.000000
	size	= 4.090000 2.460000 1.780000
}
}
SET_MODEL zombie_head001.x
{
	parent	= zombie_body001.x
	pos		= 0.000000 5.420000 0.000000
	rot		= 0.000000 0.000000 0.000000
	size	= 1.000000 1.000000 1.000000
COLLISION_BALL
{
	pos		= 0.000000 15.760000 0.000000
	len		= 2.100000
}
}
SET_MODEL zombie_left_elbow.x
{
	parent	= zombie_left_shoulder001.x
	pos		= 2.590000 0.000000 0.000000
	rot		= 0.000000 0.000000 0.000000
	size	= 1.000000 1.000000 1.000000
COLLISION_BOX
{
	pos		= 1.270000 0.000000 0.000000
	rot		= 0.000000 0.000000 0.000000
	size	= 2.630000 1.330000 1.650000
}
}
SET_MODEL zombie_left_hand001.x
{
	parent	= zombie_left_elbow.x
	pos		= 2.590000 0.000000 0.000000
	rot		= 0.000000 0.000000 0.000000
	size	= 1.000000 1.000000 1.000000
COLLISION_BOX
{
	pos		= 0.720000 0.000000 0.000000
	rot		= 0.000000 0.000000 0.000000
	size	= 1.450000 1.330000 1.730000
}
}
SET_MODEL zombie_left_shin.x
{
	parent	= zombie_left_thigh001.x
	pos		= 0.000000 -2.670000 0.000000
	rot		= 0.000000 0.000000 0.000000
	size	= 1.000000 1.000000 1.000000
COLLISION_BOX
{
	pos		= 0.000000 -1.290000 0.000000
	rot		= 0.000000 0.000000 0.000000
	size	= 1.800000 2.690000 1.670000
}
}
SET_MODEL zombie_left_shoes.x
{
	parent	= zombie_left_shin.x
	pos		= 0.000000 -2.620000 0.000000
	rot		= 0.000000 0.000000 0.000000
	size	= 1.000000 1.000000 1.000000
COLLISION_BOX
{
	pos		= 0.000000 -0.370000 -0.520000
	rot		= 0.000000 0.000000 0.000000
	size	= 1.760000 0.770000 2.770000
}
}
SET_MODEL zombie_left_shoulder001.x
{
	parent	= zombie_body001.x
	pos		= 1.950000 4.810000 0.000000
	rot		= 0.000000 0.000000 0.000000
	size	= 1.000000 1.000000 1.000000
COLLISION_BOX
{
	pos		= 1.310000 0.000000 0.000000
	rot		= 0.000000 0.000000 0.000000
	size	= 2.470000 1.330000 1.650000
}
}
SET_MODEL zombie_left_thigh001.x
{
	parent	= zombie_bottom_body001.x
	pos		= 1.150000 -2.690000 0.000000
	rot		= 0.000000 0.000000 0.000000
	size	= 1.000000 1.000000 1.000000
COLLISION_BOX
{
	pos		= 0.000000 -1.320000 0.000000
	rot		= 0.000000 0.000000 0.000000
	size	= 1.800000 2.700000 1.650000
}
}
SET_MODEL zombie_right_elbow.x
{
	parent	= zombie_right_shoulder001.x
	pos		= -2.530000 0.000000 0.000000
	rot		= 0.000000 0.000000 0.000000
	size	= 1.000000 1.000000 1.000000
COLLISION_BOX
{
	pos		= -1.300000 0.000000 0.000000
	rot		= 0.000000 0.000000 0.000000
	size	= 2.610000 1.330000 1.650000
}
}
SET_MODEL zombie_right_hand001.x
{
	parent	= zombie_right_elbow.x
	pos		= -2.590000 0.000000 0.000000
	rot		= 0.000000 0.000000 0.000000
	size	= 1.000000 1.000000 1.000000
COLLISION_BOX
{
	pos		= -0.720000 0.020000 0.000000
	rot		= 0.000000 0.000000 0.000000
	size	= 1.450000 1.330000 1.730000
}
}
SET_MODEL zombie_right_shin.x
{
	parent	= zombie_right_thigh001.x
	pos		= 0.000000 -2.670000 0.000000
	rot		= 0.000000 0.000000 0.000000
	size	= 1.000000 1.000000 1.000000
COLLISION_BOX
{
	pos		= 0.000000 -1.370000 0.000000
	rot		= 0.000000 0.000000 0.000000
	size	= 1.800000 2.690000 1.670000
}
}
SET_MODEL zombie_right_shoes.x
{
	parent	= zombie_right_shin.x
	pos		= 0.000000 -2.670000 0.000000
	rot		= 0.000000 0.000000 0.000000
	size	= 1.000000 1.000000 1.000000
COLLISION_BOX
{
	pos		= 0.000000 -0.360000 -0.550000
	rot		= 0.000000 0.000000 0.000000
	size	= 1.760000 0.770000 2.770000
}
}
SET_MODEL zombie_right_shoulder001.x
{
	parent	= zombie_body001.x
	pos		= -1.950000 4.810000 0.000000
	rot		= 0.000000 0.000000 0.000000
	size	= 1.000000 1.000000 1.000000
COLLISION_BOX
{
	pos		= -1.300000 0.000000 0.000000
	rot		= 0.000000 0.000000 0.000000
	size	= 2.430000 1.330000 1.650000
}
}
SET_MODEL zombie_right_thigh001.x
{
	parent	= zombie_bottom_body001.x
	pos		= -1.160000 -2.680000 0.000000
	rot		= 0.000000 0.000000 0.000000
	size	= 1.000000 1.000000 1.000000
COLLISION_BOX
{
	pos		= 0.000000 -1.380000 0.000000
	rot		= 0.000000 0.000000 0.000000
	size	= 1.800000 2.700000 1.650000
}
}
