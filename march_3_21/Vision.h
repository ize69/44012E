//vex-vision-config:begin
#include "vex.h"
vision::signature REDBALL (1, 4595, 8087, 6340, -1119, 81, -518, 1.400, 0);
vision::signature BLUEBALL (2, -3009, -861, -1936, 2339, 9983, 6160, 1.100, 0);
vision::signature GOAL (3, -5265, -4657, -4962, -5805, -4865, -5336, 3.000, 0);
vision::signature SIG_4 (4, 0, 0, 0, 0, 0, 0, 3.000, 0);
vision::signature SIG_5 (5, 0, 0, 0, 0, 0, 0, 3.000, 0);
vision::signature SIG_6 (6, 0, 0, 0, 0, 0, 0, 3.000, 0);
vision::signature SIG_7 (7, 0, 0, 0, 0, 0, 0, 3.000, 0);
vex::vision vision1 ( vex::PORT1, 50, REDBALL, BLUEBALL, GOAL, SIG_4, SIG_5, SIG_6, SIG_7 );
/*vex-vision-config:end*/