/* [Preview] */
// Enable preview of the crosssection.
print_view = 1; // [0:Cutted_view, 1:Print_view]

/*[Ball Bearing Dimensions]*/
// Height of the bearing.
height = 7.0;
// Inner ring radius. Half of the diameter.
inner_radius = 12/2; //[2:0.5:50]
// Inner ring radius. Half of the diameter.
outer_radius = 26.0/2; //[5:0.5:100]
// Radii of the inner and outer ring touching the housing and axis.
edge_radius = 0.5; //[0.0:0.1:2.0]
// Dimension of the rolling element.
ball_radius = 2; //[1:0.5:10]
// Edge Radii of the rolling element.
ball_edge_radius = 0.3; //[0.0:0.1:2.0]

/* [Spacing] */

/* [Spacing] */

/* [Spacing] */
// Space between the rolling element and each rin10g.
space_ball_rings = 0.2; //[0.0:0.05:0.5]
// Minimum space between the rolling elements. Effects the number of rolling elements.
min_space_between_balls = 0.25; //[0.0:0.05:1.0]
// Clearance between height of the rings and the height rolling elements. 
ball_height_space = 0.0; //[0.0:0.2:2.0]

/* [Guidance] */
// Ratio of height of the guidance elevation.
guide_size_ratio = 0.5; //[0.1:0.05:1.0]
// Elevation of the guidance element.
ball_guide_height = 0.8; //[0.1:0.1:10]

/*[Calculated Variables]*/
radi_diff = outer_radius - inner_radius;
ball_pos_radius = radi_diff/2 + inner_radius;
length_ball_pos_line = 2 * PI * ball_pos_radius;
num_balls = floor(length_ball_pos_line/(ball_radius*2+min_space_between_balls));
ball_angle_step = 360/num_balls;
guide_height = height * guide_size_ratio/2;

if (print_view==1) {
    bearing();
} else {
    difference() {
        bearing();
        translate([outer_radius/2, -outer_radius/2, height/2])
        cube([outer_radius,outer_radius, height+1], center=true);
    }
}


module bearing() {

    translate([0,0,height/2])
    union() {
        rotate_extrude($fn = 64) {
            translate([ball_pos_radius,0,0])
            union() {
                difference(){     
                    minkowski(){
                        square([radi_diff-2*edge_radius,height-2*edge_radius], center=true);
                        circle(r = edge_radius, $fn=16);
                    }
                    square([(ball_radius+space_ball_rings)*2, height + 1], center=true);
                }
                difference() {
                    for (angle = [0:180:180]) {
                        rotate([0,0,angle])    
                        translate([(ball_radius+space_ball_rings),0,0]) 
                        difference() {
                            rotate([0,0,45]) 
                            square(guide_height*sqrt(2), center=true);
                            translate([guide_height,0,0])
                            square(guide_height*2,center=true);
                        }
                    } 
                    square([(ball_radius+space_ball_rings-ball_guide_height)*2, height + 1], center=true);
                }
            }
        }
        
        for (angle_ball = [0 : ball_angle_step : 360]) {
            rotate([0,0,angle_ball])
            translate([ball_pos_radius,0,0])
            rotate_extrude($fn = 32) {
                union() {
                    translate([(ball_radius/2),0,0])
                    difference() {    
                        minkowski(){
                            square([(ball_radius-2*ball_edge_radius), height-2*ball_height_space-2*ball_edge_radius], center=true);
                            circle(r = ball_edge_radius, $fn=4);
                        }
                        translate([(ball_radius/2),0,0])
                        rotate([0,0,45])
                        square(guide_height*sqrt(2), center=true);
                    }
                    translate([((ball_radius-ball_guide_height)/2),0,0])
                    square([(ball_radius-ball_guide_height), height-ball_height_space*2], center=true);
                }
            }
        }
    }
}
