# keypoint로 부터 K번째로 가까운 좌표 찾기
>## input
1. 기준점 좌표 (x,y)가 주어진다.
2. k값이 주어진다.
3. 나머지 좌표점들의 개수가 주어진다.
4. 나머지 좌표점들이 주어진다.
>## 알고리즘 설계 방법
1. keypoint와 각 점들간의 거리를 비교할 수 있는 list를 하나 만든다. list는 key와 value를 가질 수 있는 형식이어야 한다.
2. list의 key는 keypoint와 각 점들간 거리, value로 그 key의 index를 저장한다.
4. QuickSelection으로 K번째 원소를 찾는다.
5. return형식에 맞게 데이터를 저장한다.
>## correctness
InductiveHypothesis
- nth_element는 길이 i인 list에 대해 범위 내의 K번째 원소를 찾아 줄 수 있다.

BaseCase
- 원소가 하나있는 list는 K=1번째 원소만 갖는다.

InductiveStep
1. nth_element는 길이 i인 list에 대해 K번째 원소 값을 기준으로 list의 값을 작으면 왼쪽, 크면 오른쪽으로 보낸다. K번째 원소는 K-1을 인덱싱 함으로써 찾을 수 있다.
2. i+1의 크기의 list에 대해서도 K 번째 원소를 기준으로 작은 것은 왼쪽, 큰 것은 오른쪽으로 보내며 K-1번째 인덱스를 참조하면 K번째 원소를 찾을 수 있다.

Conclusion
- nth_element는 길이 n인 list에 대해 K번째 원소를 찾아 줄 수 있다.
>## efficiency
- 첫 번째 for문에서 O(n)의 시간이 소요된다.
- nth_element는 QuickSelection으로 부분정렬을 수행한다. Expected runtime은 O(n), Worst Case의 경우 O(n*n)이다.
- 마지막 줄과 첫째 줄은O(1)의 시간이 소요된다.
- 종합하면, Expected runtime은 O(n), WorstCase runtime은 O(n*n)으로 예상된다.