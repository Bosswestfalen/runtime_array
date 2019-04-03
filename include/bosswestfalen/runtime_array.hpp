/*!
 * \file runtime_array.hpp
 * \author Bosswestfalen (https://github.com/Bosswestfalen)
 * \version 0.1.0
 * \date 2019
 * \copyright MIT License
 */


#ifndef BOSSWESTFALEN_RUNTIME_ARRAY_HPP_
#define BOSSWESTFALEN_RUNTIME_ARRAY_HPP_


#include <cstddef>
#include <initializer_list>
#include <memory>


/*!
 * \brief namespace for Bosswestfalen
 * \see https://github.com/Bosswestfalen
 */
namespace bosswestfalen
{
/*!
 * \brief Fixed size array, that can be created at runtime.
 *
 * \tparam T Type of stored elements.
 *
 * \todo rethink use of std::allocator
 */
template <typename T>
class runtime_array final
{
  public:
    /// size type
    using size_type = std::size_t;

    /// alias for T
    using value_type = T;

    /// alias for T&
    using reference = T&;

    /// alias for T const&
    using const_reference = T const&;

    /// alias for T*
    using pointer = T*;

    /*!
     * \brief default ctor for empty array
     *
     * Create an empty runtime_array.
     */
    runtime_array() = default;

    /*!
     * \brief create with given size
     *
     * \param n number of elements
     *
     * \todo is uninitialized_default_construct_n correct?
     */
    explicit runtime_array(size_type const n)
        : m_size{n}
        , m_data{std::allocator<value_type>{}.allocate(m_size)}
    {
        std::uninitialized_default_construct_n(m_data, m_size);
    }

    /*!
     * \brief create with given size and initialise with value
     *
     * \param n number of elements
     * \param value value used to initialise elements
     */
    runtime_array(size_type const n,
                  const_reference value)
        : m_size{n}
        , m_data{std::allocator<value_type>{}.allocate(m_size)}
    {
        std::uninitialized_fill_n(m_data, n, value);
    }

    /*!
     * \brief create array and fill with initializer list content
     *
     * \param il elements used to initialise
     */
    runtime_array(std::initializer_list<value_type> il)
        : m_size{il.size()}
        , m_data{std::allocator<value_type>{}.allocate(m_size)}
    {
        std::uninitialized_copy_n(il.begin(), m_size, m_data);
    }

    /// release memory
    ~runtime_array()
    {
        std::destroy_n(m_data, m_size);
        std::allocator<value_type>{}.deallocate(m_data, m_size);
    }

    /// disabled for now
    runtime_array(runtime_array const&) = delete;
    /// disabled for now
    runtime_array(runtime_array&&) = delete;
    /// disabled for now
    runtime_array& operator=(runtime_array const&) = delete;
    /// disabled for now
    runtime_array& operator=(runtime_array&&) = delete;

    /// check for emptiness
    [[nodiscard]] auto empty() const noexcept
    {
        return size() == 0;
    }

    /// get number of elements
    [[nodiscard]] auto size() const noexcept
    {
        return m_size;
    }

  private:
    /// number of elements
    size_type m_size{0};

    /// array of the elements
    pointer m_data{nullptr};
};

} // namespace bosswestfalen

#endif

