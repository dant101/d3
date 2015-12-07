 * General Workflow of d3
 * 
 * SESSION2 is called creating a session of unconnected machines
 * MACHINE is called which attempts to connect to a session
 * MACHINESTATUS is called which updates the machine in each of it's sessions it's connected to
 * 
 * Every TIME_UPDATE, all sessions are printed to console
 * If a machine doesn't communicate for TIMEOUT seconds, assume it's connection has been lost
