#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <tuple>
#include <numeric>
#include <algorithm>

using namespace std;


class Solution {
public:

    int minimumFinishTime(vector<vector<int>> &tires, int changeTime, int numLaps) {
        // 初始化一个大小为 18 的数组，初始值为 INT_MAX / 2
        // 除二是防止下面计算状态转移时溢出
        // minSec[x] 表示 完成 x 轮，不换轮胎 所需要的最少时间
        vector<int> minSec(18, INT_MAX / 2);
        for (auto &tire : tires) {
            long time = tire[0];
            for (int x = 1, sum = 0; time <= changeTime + tire[0]; ++x) {
                sum += time;
                minSec[x] = min(minSec[x], sum);
                time *= tire[1];
            }
        }

        vector<int> f(numLaps + 1, INT_MAX);  // f[i] 表示跑 i 圈所需要的最少时间
        f[0] = -changeTime;
        for (int i = 1; i <= numLaps; ++i) {
            // f[i] 最多从 f[i - 17] 进化而来
            for (int j = 1; j <= min(17, i); ++j)
                f[i] = min(f[i], f[i - j] + minSec[j]);
            f[i] += changeTime;
        }
        return f[numLaps];
    }
};