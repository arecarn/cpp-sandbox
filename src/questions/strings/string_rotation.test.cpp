// String Rotation: Assume you have a method is_substring which checks if one
// word is a substring of another. Given two strings, sl and s2, write code to
// check if s2 is a rotation of sl using only one call to is_substring (e.g.,
// "waterbottle" is a rotation of"erbottlewat")

#include <gtest/gtest.h>
#include <string>

bool is_substring(std::string_view s1, std::string_view s2)
{
    return s1.find(s2) != std::string::npos;
}

bool string_rotation(std::string s1, std::string s2)
{
    if (s1.size() != s2.size())
    {
        return false;
    }

    int match_count = 0;
    int i = 0;

    while ((i + match_count) < s2.size())
    {
        if (s1[match_count] == s2[i + match_count])
        {
            match_count++;
            std::cerr << match_count << ", " << i << "\n";
            if (i + match_count == s1.size())
            {
                return is_substring(
                    s2,
                    std::string_view{s1}.substr(match_count));
            }
        }
        else
        {
            match_count = 0;
            i++;
        }
    }
    return false;
}

TEST(string_rotation, test1)
{

    ASSERT_TRUE(string_rotation("cca", "cac"));
    ASSERT_TRUE(string_rotation("cac", "cca"));
    ASSERT_TRUE(string_rotation("snackcatcat", "catsnackcat"));
    ASSERT_TRUE(string_rotation("catsnackcat", "snackcatcat"));
    ASSERT_TRUE(string_rotation("erbottlewat", "waterbottle"));
    ASSERT_TRUE(string_rotation("waterbottle", "erbottlewat"));

    ASSERT_FALSE(string_rotation("ccc", "cac"));
    ASSERT_FALSE(string_rotation("cab", "cca"));
    ASSERT_FALSE(string_rotation("ssackcatcat", "catsnackcat"));
    ASSERT_FALSE(string_rotation("catsnakkcat", "snackcatcat"));
    ASSERT_FALSE(string_rotation("wrbottlewat", "waterbottle"));
    ASSERT_FALSE(string_rotation("eaterbottle", "erbottlewat"));
}
