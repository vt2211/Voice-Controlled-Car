#Our calculated parameters
theta_left = .3031
theta_right = .2664
beta_left = -32.56
beta_right = -37.35
v_star = 73.3

params = np.array([(theta_left, theta_right), (beta_left, beta_right)])
d0 = (0,  0)
sim_length = 10 # sim length
mismatch_error = 0.1 # 10% model mismatch