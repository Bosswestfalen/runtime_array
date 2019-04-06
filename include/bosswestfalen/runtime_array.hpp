/*!
 * \file runtime_array.hpp
 * \author Bosswestfalen (https://github.com/Bosswestfalen)
 * \version 0.4.0
 * \date 2019
 * \copyright MIT License
 */


#ifndef BOSSWESTFALEN_RUNTIME_ARRAY_HPP_
#define BOSSWESTFALEN_RUNTIME_ARRAY_HPP_


#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <utility>


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

    /// alias for T const *;
    using const_pointer = T const*;

    /// alias for T*
    using iterator = T*;

    /// alias for T const*
    using const_iterator = T const*;

    /// alias for T* for reversed iteration
    using reverse_iterator = std::reverse_iterator<iterator>;

    /// alias for T const* for reversed iteration
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

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

    /// destroy objects and release memory
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
    [[nodiscard]] auto empty() const noexcept -> bool
    {
        return size() == 0;
    }

    /// get number of elements
    [[nodiscard]] auto size() const noexcept -> size_type
    {
        return m_size;
    }

    /// get direct access to the data
    [[nodiscard]] auto data() const noexcept -> const_pointer
    {
        return m_data;
    }

    /// \copydoc data()
    [[nodiscard]] auto data() noexcept -> pointer
    {
        return const_cast<pointer>(std::as_const(*this).data());
    }

    /*!
     * \brief get reference to specified element
     *
     * Returns a reference to the element at specified position.
     * \note No bounds checking is performed.
     *
     * \param pos position of the element
     * \return reference of the element
     */
    [[nodiscard]] auto operator[](size_type const pos) const -> const_reference
    {
        return *(data() + pos);
    }

    /// \copydoc operator[]
    [[nodiscard]] auto operator[](size_type const pos) -> reference
    {
        return const_cast<reference>(std::as_const(*this)[pos]);
    }

    /*!
     * \brief get reference to specified element
     *
     * Returns a reference to the element at specified position.
     * \note Bounds checking is performed.
     *
     * \param pos position of the element
     * \return reference of the element
     */
    [[nodiscard]] auto at(size_type const pos) const -> const_reference
    {
        if (size() <= pos)
        {
            throw std::out_of_range{""};
        }
        return operator[](pos);
    }

    /// \copydoc at
    [[nodiscard]] auto at(size_type const pos) -> reference
    {
        return const_cast<reference>(std::as_const(*this).at(pos));
    }

    /// get reference to the first element
    [[nodiscard]] auto front() const -> const_reference
    {
        return operator[](0);
    }

    /// \copydoc front
    [[nodiscard]] auto front() -> reference
    {
        return const_cast<reference>(std::as_const(*this).front());
    }
    
    /// get reference to the last element
    [[nodiscard]] auto back() const -> const_reference
    {
        return operator[](size() - 1);
    }

    /// \copydoc back
    [[nodiscard]] auto back() -> reference
    {
        return const_cast<reference>(std::as_const(*this).back());
    }

    /// get iterator to first element
    [[nodiscard]] auto cbegin() const noexcept -> const_iterator
    {
        return data();
    }

    /// \copydoc cbegin()
    [[nodiscard]] auto begin() const noexcept -> const_iterator
    {
        return cbegin();
    }

    /// \dopydoc begin()
    [[nodiscard]] auto begin() noexcept -> iterator
    {
        return const_cast<iterator>(std::as_const(*this).begin());
    }

    /// get iterator to the "element" following the last element
    [[nodiscard]] auto cend() const noexcept -> const_iterator
    {
        return (data() + size());
    }
    
    /// \copydoc end()
    [[nodiscard]] auto end() const noexcept -> const_iterator
    {
        return cend();
    }

    /// \copydoc end()
    [[nodiscard]] auto end() noexcept -> iterator
    {
        return const_cast<iterator>(std::as_const(*this).end());
    }
    
    /// get reverse iterator to the last element
    [[nodiscard]] auto crbegin() const noexcept -> const_reverse_iterator
    {
        return const_reverse_iterator{cend()};
    }

    /// \copydoc crbegin()
    [[nodiscard]] auto rbegin() const noexcept -> const_reverse_iterator
    {
        return crbegin();
    }

    /// \dopydoc rbegin()
    [[nodiscard]] auto rbegin() noexcept -> reverse_iterator
    {
        return reverse_iterator{end()};
    }

    /// get reverse iterator to the "element" before the first element
    [[nodiscard]] auto crend() const noexcept -> const_reverse_iterator
    {
        return const_reverse_iterator{cbegin()};
    }
    
    /// \copydoc rend()
    [[nodiscard]] auto rend() const noexcept -> const_reverse_iterator
    {
        return crend();
    }

    /// \copydoc rend()
    [[nodiscard]] auto rend() noexcept -> reverse_iterator
    {
        return reverse_iterator{begin()};
    }

    /// assign given value to all elements
    void fill(value_type const& val)
    {
        std::fill_n(data(), size(), val);
    }

  private:
    /// number of elements
    size_type m_size{0};

    /// array of the elements
    pointer m_data{nullptr};
};

} // namespace bosswestfalen

#endif

