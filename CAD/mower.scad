$fn = 256;

width_lemet = 120;
depth_lemet = 20;
height_lemet = 4;

//shaft
height_shaft = 20;
width_shaft_r = 4; 
bore_shaft_r = 1;


// lemet
difference(){
    
difference(){
    translate([0,0,height_lemet/2]) cube([width_lemet, depth_lemet, height_lemet], center= true);
    
        //outside cut-out to provide smooth rotation.
        difference(){
        translate([0,0,height_lemet/2]) cube([width_lemet, depth_lemet, height_lemet], center= true);
        translate([0,0,height_lemet/2]) cylinder(h = height_lemet, r = width_lemet/2, center= true);
        }
}

translate([width_shaft_r,-depth_lemet/2, 0]) 
rotate([atan(height_lemet/depth_lemet),0, 0]) 
cube([width_lemet/2-width_shaft_r, sqrt(depth_lemet^2+width_shaft_r^2), height_lemet]);

rotate([0,0,180])
translate([width_shaft_r,-depth_lemet/2, 0]) 
rotate([atan(height_lemet/depth_lemet),0, 0]) 
cube([width_lemet/2-width_shaft_r, sqrt(depth_lemet^2+width_shaft_r^2), height_lemet]);
}

difference(){
    translate([0 , 0, height_shaft/2]) cylinder(h = height_shaft, r = width_shaft_r, center = true);
    translate([0 , 0, height_shaft/2]) cylinder(h = height_shaft, r = bore_shaft_r, center = true);
}

//create lemet

