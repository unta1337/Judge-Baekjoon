# 12865: 평범한 배낭
#
# 물품의 무게와 가치, 배낭의 최대 적재 용량이 주어졌을 때, 가능한 가치의 최댓값을 구하여라.
#
# https://www.acmicpc.net/problem/12865

# 메모리: 226652 KB
# 시간: 5852 ms
# 코드 길이: 1400 bytes
# http://boj.kr/26d9f11073894e5d9980b15c378d07d8

def main():
    # 입력.
    N, K = list(map(int, input().split(' ')))

    # DP.
    table = [[0 for _ in range(K + 1)] for _ in range(N + 1)]

    # 사용자 입력.
    items = [{'weight': 0, 'value': 0}]
    for i in range(N):
        W, V = list(map(int, input().split(' ')))
        items.append({'weight': W, 'value': V})

    max_value = 0
    for item_index in range(1, N + 1):
        for weight_index in range(1, K + 1):
            # 현재 물건의 가치 + 남은 공간에 담을 수 있는 최대 가치.
            current_max_value = items[item_index].get('value') + table[item_index - 1][weight_index - items[item_index].get('weight')] if items[item_index].get('weight') <= weight_index else 0

            # 이전 선택 중 가장 높은 가치.
            alt_max_value = table[item_index - 1][weight_index]

            # 위의 두 경우 중 더 나은 선택을 취함.
            table[item_index][weight_index] = current_max_value if current_max_value > alt_max_value else alt_max_value
            max_value = table[item_index][weight_index] if table[item_index][weight_index] > max_value else max_value

    print(max_value)

if __name__ == '__main__':
    main()