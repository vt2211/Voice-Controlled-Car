def drive_straight_left_cl(v_star, delta):
    return drive_straight_left_ol(v_star)-(f_left/theta_left)*delta

def drive_straight_right_cl(v_star, delta):
    return  drive_straight_right_ol(v_star)+(f_right/theta_right)*delta