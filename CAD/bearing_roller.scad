//Bearing 608 dimmentions
608_in_d = 8; //8mm hole diameter
608_out_d = 22;
608_width = 7;

tollerance = 0.0;

//Following wheel dimentions
follow_wheel_out_d = 608_out_d + (3 * 2); //3mm on each side
follow_wheel_in_d = 608_out_d + tollerance;
follow_wheel_cover_cap_depth = 1;
follow_wheel_depth = 608_width + follow_wheel_cover_cap_depth;

$fn=100;

linear_extrude(follow_wheel_depth)
difference()
{
    circle(d = follow_wheel_out_d);
    circle(d = follow_wheel_in_d);   
};
translate(0,0,-(follow_wheel_depth/2+follow_wheel_cover_cap_depth)) 
linear_extrude(follow_wheel_cover_cap_depth) 
difference(){
    circle(d = follow_wheel_out_d);
    circle(d = 608_in_d);
};