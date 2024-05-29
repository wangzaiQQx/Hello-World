# class Solution:
#     def lengthOfLongestSubstring(self, s: str) -> int:
#         if len(s) <= 1:
#             return len(s)
        
#         char_index_map = {}
#         left = 0
#         max_length = 0
        
#         for right in range(len(s)):
#             if s[right] in char_index_map and char_index_map[s[right]] >= left:
#                 left = char_index_map[s[right]] + 1
            
#             char_index_map[s[right]] = right
#             max_length = max(max_length, right - left + 1)
        
#         return max_length

# class Solution:
#     def lengthOfLongestSubstring(self, s: str) -> int:
#         dic = {}
#         max_len = 0
#         start = 0  # This marks the start of the non-repeating substring
        
#         for i, char in enumerate(s):
#             if char in dic and dic[char] >= start:
#                 # If character is repeated and the last occurrence is after or at 'start'
#                 start = dic[char] + 1  # Move start right after the last occurrence
#             dic[char] = i  # Update last occurrence of char to current index
            
#             # Calculate the current length of the substring
#             current_length = i - start + 1
#             if current_length > max_len:
#                 max_len = current_length
        
#         return max_len  


# class Solution:
#     def lengthOfLongestSubstring(self, s: str) -> int:
#         hashmap = {}
#         start = -1
#         max_len = 0

#         for i,ch in enumerate(s):
#             if ch in hashmap and hashmap[ch]>start:
#                 start = hashmap[ch]
#             hashmap[ch] = i

#             max_len = max(i - start, max_len)

#         return max_len

class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        hashmap,start,max_len = {}, -1, 0

        for i,ch in enumerate(s):
            start = max(start, hashmap.get(ch,-1))
            hashmap[ch] = i
            max_len = max(i - start, max_len)

        return max_len
    
def test():
    sol = Solution()
    li = [""," ","abcabcbb", "bbbbb", "pwwkew", "au", "abba"]
    # li = ["pwwkew"]
    # li = ["adwdfadffda"]
    for s in li:
        result = sol.lengthOfLongestSubstring(s)
        print(result)

if __name__ == "__main__":
    test() 