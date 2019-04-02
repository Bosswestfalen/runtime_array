/*!
 * \file runtime_array.hpp
 * \author Bosswestfalen (https://github.com/Bosswestfalen)
 * \version 0.0.1
 * \date 2019
 * \copyright MIT License
 */


#ifndef BOSSWESTFALEN_RUNTIME_ARRAY_HPP_
#define BOSSWESTFALEN_RUNTIME_ARRAY_HPP_


/*!
 * \brief namespace for Bosswestfalen
 * \see https://github.com/Bosswestfalen
 */
namespace bosswestfalen
{
/*!
 * \brief Fixed size array, that can be created at runtime.
 *
 * \todo Add functionality and docs.
 */
class runtime_array final
{
  public:
    // this implementation is for testing
    [[nodiscard]] auto empty() const noexcept -> bool
    {
        return true;
    }

};

} // namespace bosswestfalen

#endif

