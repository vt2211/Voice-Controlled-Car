def identify_parameters(u, v):
    ones = -1 * np.ones(np.shape(np.vstack(u)))
    data = np.hstack((np.vstack(u), ones))
    lstsq = np.linalg.lstsq(data, v)
    return lstsq[0][0], lstsq[0][1]

theta_left, beta_left = identify_parameters(u, vleft)
theta_right, beta_right = identify_parameters(u, vright)

print("float theta_left = {:.4g};".format(theta_left))
print("float theta_right = {:.4g};".format(theta_right))
print("float beta_left = {:.4g};".format(beta_left))
print("float beta_right = {:.4g};".format(beta_right))

u = u.reshape(-1)
vleft_LS = theta_left*u-beta_left
vright_LS = theta_right*u-beta_right
plt.plot(u, vleft, 'bo',  u, vright, 'yo', u, vleft_LS, 'b-', u, vright_LS, 'y-')
plt.xlabel("u (input via PWM)")
plt.ylabel("Velocity of Wheels")
plt.legend(("left", "right"), loc=0)