 * General Workflow of d3
 * 
 * SESSION2 is called creating a session of unconnected machines, sessions with the same name are overridden
 * MACHINE is called which attempts to connect to it's relevant session, machines with the same name are overriden
 * MACHINESTATUS is called which updates all relevant machines in each session with fps and version info
 * 
 * Every TIME_UPDATE, all sessions are printed to console
 * If a machine doesn't communicate for TIMEOUT seconds, assume it's connection has been lost
