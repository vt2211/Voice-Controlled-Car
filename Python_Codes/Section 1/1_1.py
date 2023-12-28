freq_Vpp = {
    100: 1.4,
    200: 1.6, 
    300: 1.9, 
    500: 2.6, 
    800: 2.4, 
    1000: 5, 
    1250: 4.8, 
    1750: 5, 
    2000: 4.9,  
    3000: 4.6, 
    4000: 3.4, 
    5000: 3.5, 
    6000: 5, 
    7000: 5, 
    8000: 3.9,
    10000: 1.5,
    15000: 1
}
freq = sorted(list(freq_Vpp.keys()))
Vpp = [freq_Vpp[f] for f in freq] 
print("Vpp = ", Vpp)

# We do not have a measurable input signal Vin, so we normalize the maximum of the frequency response to 1.
gain = np.array(Vpp)/max(Vpp)

plt.loglog(freq, gain)
plt.title('log-Gain vs. log-Frequency')
plt.xlabel('Frequency (Hz)')
plt.ylabel('Gain (Volts/Volts)')