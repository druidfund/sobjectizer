/*
	SObjectizer 5.
*/

/*!
 * \file
 * \brief Private interface for a coop.
 *
 * \since
 * v.5.6.0
 */

#pragma once

#include <so_5/coop.hpp>

namespace so_5
{

namespace impl
{

//
// coop_private_iface_t
//
/*!
 * \since
 * v.5.2.3
 *
 * \brief A special class for accessing private members of agent_coop.
 */
class coop_private_iface_t
{
	public :
		static coop_unique_holder_t
		make_coop(
			coop_id_t id,
			coop_handle_t parent,
			disp_binder_shptr_t default_binder,
			outliving_reference_t< environment_t > env )
			{
				return {
						coop_shptr_t {
								new coop_t{
									id,
									std::move(parent),
									std::move(default_binder),
									env
								},
								coop_t::destroy
						}
				};
			}

		static coop_shptr_t
		make_from( coop_unique_holder_t holder ) noexcept
			{
				return holder.release();
			}

		static void
		increment_usage_count( coop_t & coop ) noexcept
			{
				coop.increment_usage_count();
			}

		static void
		decrement_usage_count( coop_t & coop )
			{
				coop.decrement_usage_count();
			}

		static void
		do_registration_specific_actions( coop_t & coop )
			{
				coop_impl_t::do_registration_specific_actions( coop );
			}

		static void
		do_final_deregistration_actions( coop_t & coop )
			{
				coop_impl_t::do_final_deregistration_actions( coop );
			}

		static void
		call_reg_notificators( coop_t & coop ) noexcept
			{
				if( coop.m_reg_notificators )
					coop.m_reg_notificators->call_all(
							coop.environment(),
							coop.handle() );
			}

		static void
		call_dereg_notificators( coop_t & coop ) noexcept
			{
				if( coop.m_dereg_notificators )
					coop.m_dereg_notificators->call_all(
							coop.environment(),
							coop.handle(),
							dereg_reason( coop ) );
			}

		static coop_dereg_reason_t
		dereg_reason( const coop_t & coop ) noexcept
			{
				return coop.m_dereg_reason;
			}
};

} /* namespace impl */

} /* namespace so_5 */

