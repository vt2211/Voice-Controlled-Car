min_vel = max(min(vleft_LS), min(vright_LS))
max_vel = min(max(vleft_LS), max(vright_LS))

if ((min(vleft_LS) > max(vright_LS)) or (min(vright_LS) > max(vleft_LS))):
    print('Error: Velocity ranges of left and right wheels do not overlap. Recollect data_fine with a wider PWM range')
else:
    print('Velocity range = [{:0.1f}, {:0.1f}]'.format(min_vel, max_vel))
    midpoint = (min_vel+max_vel)/2
    print('\nOperating point:\nfloat v_star = {:.1f};'.format(midpoint))

    u = u.reshape(-1)
    vleft_LS = theta_left*u-beta_left
    vright_LS = theta_right*u-beta_right
    plt.plot(u, vleft_LS, 'b-', u, vright_LS, 'y-')
    for i in (min_vel, max_vel):
        plt.plot(u, 0*u + i, 'g-')
    plt.plot(u, vleft, 'bo',  u, vright, 'yo')
    plt.xlabel("u (input via PWM)")
    plt.ylabel("Velocity of Wheels")
    plt.legend(("left", "right", "overlap"), loc=0)